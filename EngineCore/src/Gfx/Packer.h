#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "../Types.h"

namespace Shard
{
	namespace Gfx
	{
		struct PackerNode
		{
			bool Used;
			uint X, Y;
			uint Width, Height;
			PackerNode* Down;
			PackerNode* Right;

			PackerNode(bool used, uint x, uint y, uint w, uint h, PackerNode* down, PackerNode* right)
				: Used(used), X(x), Y(y), Width(w), Height(h), Down(down), Right(right)
			{
			}

			PackerNode(uint x, uint y, uint w, uint h)
				: PackerNode(false, x, y, w, h, nullptr, nullptr)
			{
			}

			~PackerNode()
			{
				if (Down)
					delete Down;
				if (Right)
					delete Right;
			}
		};

		template <typename T>
		struct PackerEntry
		{
			uint Width, Height;
			PackerNode* Node;
			T Key;

			PackerEntry(T k, uint width, uint height)
				: Key(k), Width(width), Height(height), Node(nullptr)
			{
			}
		};

		struct PackerResult
		{
			uint X, Y;
			uint Width, Height;

			PackerResult(uint x, uint y, uint w, uint h)
				: X(x), Y(y), Width(w), Height(h)
			{
			}
		};

		enum class PackerSorting
		{
			Width, Height, GreaterSide, Area
		};

		template <typename T>
		class Packer
		{
		private:
			static PackerSorting s_SortingMode;

		private:
			PackerNode* m_Root;
			std::vector<PackerEntry<T>> m_Entries;
			uint m_PackWidth;
			uint m_PackHeight;
			std::map<T, PackerResult> m_PackedElements;

		public:
			Packer()
				: m_Root(nullptr)
			{
			}

			~Packer()
			{
			}

			inline void Push(T k, uint w, uint h)
			{
				m_Entries.push_back(PackerEntry<T>(k, w, h));
			}

			void Pack()
			{
				m_PackedElements.clear();

				// Sort the entries descending
				switch (s_SortingMode)
				{
				case PackerSorting::Width:
					std::sort(m_Entries.begin(), m_Entries.end(), packer_sort_width);
					break;

				case PackerSorting::Height:
					std::sort(m_Entries.begin(), m_Entries.end(), packer_sort_height);
					break;

				case PackerSorting::GreaterSide:
					std::sort(m_Entries.begin(), m_Entries.end(), packer_sort_maxside);
					break;

				case PackerSorting::Area:
					std::sort(m_Entries.begin(), m_Entries.end(), packer_sort_area);
					break;
				}
				
				uint w = m_Entries.empty() ? 0 : m_Entries[0].Width;
				uint h = m_Entries.empty() ? 0 : m_Entries[0].Height;
				m_Root = new PackerNode(0, 0, w, h);

				PackerNode* node = nullptr;
				for (PackerEntry<T>& block : m_Entries)
				{
					if (node = FindNode(m_Root, block.Width, block.Height))
						block.Node = SplitNode(node, block.Width, block.Height);
					else
						block.Node = AddNode(block.Width, block.Height);
				}

				for (PackerEntry<T>& e : m_Entries)
					m_PackedElements.insert(std::make_pair(e.Key, PackerResult(e.Node->X, e.Node->Y, e.Width, e.Height)));

				m_PackWidth = m_Root->Width;
				m_PackHeight = m_Root->Height;

				delete m_Root;
				m_Entries.clear();
			}

			inline const PackerResult& Get(T key) const
			{
				return m_PackedElements.find(key)->second;
			}

			inline uint GetPackWidth() const { return m_PackWidth; }
			inline uint GetPackHeight() const { return m_PackHeight; }

		private:
			PackerNode* FindNode(PackerNode* root, uint w, uint h) const
			{
				if (root->Used)
				{
					PackerNode* node = FindNode(root->Right, w, h);
					if (node)
						return node;

					return FindNode(root->Down, w, h);
				}
				else if (w <= root->Width && h <= root->Height)
					return root;

				return nullptr;
			}

			inline PackerNode* SplitNode(PackerNode* node, uint w, uint h)
			{
				node->Used = true;
				node->Down = new PackerNode(node->X, node->Y + h, node->Width, node->Height - h);
				node->Right = new PackerNode(node->X + w, node->Y, node->Width - w, h);
				return node;
			}

			PackerNode* AddNode(uint w, uint h)
			{
				bool canDown = (w <= m_Root->Width);
				bool canRight = (h <= m_Root->Height);

				// Keep it square
				bool shouldRight = canRight && (m_Root->Height >= (m_Root->Width + w));
				bool shouldDown = canDown && (m_Root->Width >= (m_Root->Height + h));

				if (shouldRight)
					return AddRight(w, h);
				else if (shouldDown)
					return AddDown(w, h);
				else if (canRight)
					return AddRight(w, h);
				else if (canDown)
					return AddDown(w, h);

				return nullptr;
			}

			PackerNode* AddRight(uint w, uint h)
			{
				m_Root = new PackerNode(true, 0, 0, m_Root->Width + w, m_Root->Height, m_Root, new PackerNode(m_Root->Width, 0, w, m_Root->Height));
				PackerNode* node = nullptr;
				if (node = FindNode(m_Root, w, h))
					return SplitNode(node, w, h);

				return nullptr;
			}

			PackerNode* AddDown(uint w, uint h)
			{
				m_Root = new PackerNode(true, 0, 0, m_Root->Width, m_Root->Height + h, new PackerNode(0, m_Root->Height, m_Root->Width, h), m_Root);
				PackerNode* node = nullptr;
				if (node = FindNode(m_Root, w, h))
					return SplitNode(node, w, h);

				return nullptr;
			}

		private:
			static inline bool packer_sort_width(PackerEntry<T>& a, PackerEntry<T>& b) { return a.Width > b.Width; }
			static inline bool packer_sort_height(PackerEntry<T>& a, PackerEntry<T>& b) { return a.Height > b.Height; }
			static inline bool packer_sort_maxside(PackerEntry<T>& a, PackerEntry<T>& b) { return std::max(a. Width, a.Height) > std::max(b.Width, b.Height); }
			static inline bool packer_sort_area(PackerEntry<T>& a, PackerEntry<T>& b) { return a.Width * a.Height > b.Width * b.Height; }

		public:
			static inline void SetSortingMode(PackerSorting s) { s_SortingMode = s; }
		};

		template <typename T>
		PackerSorting Packer<T>::s_SortingMode = PackerSorting::GreaterSide;
	}
}