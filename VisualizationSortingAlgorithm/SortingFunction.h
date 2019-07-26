//! @file
//! \brief Библиотека функций сортировки
#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include <queue>

namespace sorting
{
	//! \class heap 
	//! \brief Класс кучи
	template <typename T>
	class heap
	{
	public:
		int size = 0; ///< размер кучи

	private:
		std::vector<T> tree;
		//! \brief Функция инициализации кучи
		void heap_init(int Size)
		{
			std::vector<T> empty;
			size = Size;
			tree = empty;
		}
		
		void descent_down(int vertex, int* swaping, int* comparisons)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);

			const int child = 2 * vertex;
			int minIndexOfChild = vertex;
			if (child < size && tree[child] < tree[minIndexOfChild])
				minIndexOfChild = child;
			(*comparisons)++;
			if (child + 1 < size && tree[child + 1] < tree[minIndexOfChild])
				minIndexOfChild = child + 1;
			(*comparisons)++;

			if (minIndexOfChild != vertex)
			{
				std::swap(tree[minIndexOfChild],tree[vertex]);
				(*swaping)++;
				descent_down(minIndexOfChild, swaping, comparisons);
			}
		}

		//! \brief Функция получения минимального значения и удаления его
		T extract_min(int* swaping, int* comparisons)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);

			T minValue = get_min();
			tree[0] = tree[size-1];
			(*swaping)++;
			size -= 1;
			tree.pop_back();
			descent_down(0, swaping, comparisons);

			return minValue;
		}
	public:
		heap()
		{
			heap_init(0);
		}

		//! \brief Функция создания кучи
		void make_heap(int* swaping, int* comparisons, std::vector<T>Array, int n)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);

			heap_init(n);
			for (int i = 0; i < n; i++)
				tree.push_back(Array[i]);
			for (int i = n - 1; i >= 0; i--)
				descent_down(i, swaping, comparisons);
		}

		//! \brief возрашает минимальный элемент кучи
		T get_min()
		{
			return tree[0];
		}
		
		//! \brief Функция сортировки кучей
		//!
		//! \param[out] swaping			число обменов
		//! \param[out] comparisons		число сравнений
		//! \param[out] Array			сортеруемый массив
		//! \param n					число элементов для сортировки от 0
		/*! Код функции выглядит следующим образом :
			\code
			void heap_sort(int* swaping, int* comparisons, std::vector<T>* Array, int n)
			{
				assert(swaping != nullptr);
				assert(comparisons != nullptr);
				assert(swaping != comparisons);
				assert(Array != nullptr);

				make_heap(swaping, comparisons, *Array, n);
				for (int i = 0; i < n; i++)
				{
					(*Array)[i] = extract_min(swaping, comparisons);
					(*swaping)++;
				}
			}
			\endcode
		*/
		void heap_sort(int* swaping, int* comparisons, std::vector<T>* Array, int n)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);
			assert(Array != nullptr);

			make_heap(swaping, comparisons, *Array, n);
			for (int i = 0; i < n; i++)
			{
				(*Array)[i] = extract_min(swaping, comparisons);
				(*swaping)++;
			}
		}
	};

	//! \brief   Сортировка вставкой
	//!
	//! \param[out] swaping			число обменов
	//! \param[out] comparisons		число сравнений
	//! \param[out] Array			сортеруемый массив
	//! \param n					число элементов для сортировки от 0
	/*! Код функции выглядит следующим образом :
		\code
		void insertionSorting(int* swaping, int* comparisons, std::vector<int>* Array, int n)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);
			assert(Array != nullptr);

			for (int i = 0; i < n; i++)
			{
				int j = i;
				while (j > 0 && (*Array)[j] < (*Array)[j - 1])
				{
					(*comparisons)++;
					std::swap((*Array)[j], (*Array)[j - 1]);
					(*swaping)++;
					j -= 1;
				}
			}
		}
		\endcode
	*/
	void insertionSorting(int* swaping, int* comparisons, std::vector<int>* Array, int n)
	{
		assert(swaping != nullptr);
		assert(comparisons != nullptr);
		assert(swaping != comparisons);
		assert(Array != nullptr);

		for (int i = 0; i < n; i++)
		{
			int j = i;
			while (j > 0 && (*Array)[j] < (*Array)[j - 1])
			{
				(*comparisons)++;
				std::swap((*Array)[j], (*Array)[j - 1]);
				(*swaping)++;
				j -= 1;
			}
		}
	}

	//! \brief   Сортировка пузырьком
	//!
	//! \param[out] swaping			число обменов
	//! \param[out] comparisons		число сравнений
	//! \param[out] Array			сортеруемый массив
	//! \param n					число элементов для сортировки от 0
	/*! Код функции выглядит следующим образом :
		\code
		void bubleSorting(int* swaping, int* comparisons, std::vector<int>* Array, int n)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);
			assert(Array != nullptr);

			bool end = false;
			while (!end)
			{
				end = true;
				for (int i = 1; i < n; i++)
				{
					if ((*Array)[i] < (*Array)[i - 1])
					{
						(*comparisons)++;
						std::swap((*Array)[i], (*Array)[i - 1]);
						(*swaping)++;
						end = false;
					}
				}
				n--;
			}
		}
		\endcode
	*/
	void bubleSorting(int* swaping, int* comparisons, std::vector<int>* Array, int n)
	{
		assert(swaping != nullptr);
		assert(comparisons != nullptr);
		assert(swaping != comparisons);
		assert(Array != nullptr);

		bool end = false;
		while (!end)
		{
			end = true;
			for (int i = 1; i < n; i++)
			{
				if ((*Array)[i] < (*Array)[i - 1])
				{
					(*comparisons)++;
					std::swap((*Array)[i], (*Array)[i - 1]);
					(*swaping)++;
					end = false;
				}
			}
			n--;
		}
	}

	void merge(int* swaping, int* comparisons, std::vector<int>* Array, int left, int middle, int right)
	{
		assert(swaping != nullptr);
		assert(comparisons != nullptr);
		assert(swaping != comparisons);
		assert(Array != nullptr);

		int i = middle+1;
		int j = left;
		std::vector<int>merged;

		while (i <= right && j <= middle)
		{
			if ((*Array)[i] <= (*Array)[j])
				merged.push_back((*Array)[i++]);
			else
				merged.push_back((*Array)[j++]);
			(*comparisons)++;
			(*swaping)++;
		}
		while (j <= middle)
		{
			merged.push_back((*Array)[j++]);
			(*swaping)++;
		}
		while (i <= right)
		{
			merged.push_back((*Array)[i++]);
			(*swaping)++;
		}

		for (i=left; i <= right; i++)
		{
			(*Array)[i] = merged[i - left];
			(*swaping)++;
		}
	}

	//! \brief   Сортировка вставкой
	//!
	//! \param[out] swaping			число обменов
	//! \param[out] comparisons		число сравнений
	//! \param[out] Array			сортеруемый массив
	//! \param left					начало сортируемого участка
	//! \param right				конец сортируемого участка
	//! merge() функция объединяет два отсортированных участка массива в один отсортированный
	/*! Код функции выглядит следующим образом :
		\code
		void merge(int* swaping, int* comparisons, std::vector<int>* Array, int left, int middle, int right)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);
			assert(Array != nullptr);

			int i = middle+1;
			int j = left;
			std::vector<int>merged;

			while (i <= right && j <= middle)
			{
				if ((*Array)[i] <= (*Array)[j])
					merged.push_back((*Array)[i++]);
				else
					merged.push_back((*Array)[j++]);
				(*comparisons)++;
				(*swaping)++;
			}
			while (j <= middle)
			{
				merged.push_back((*Array)[j++]);
				(*swaping)++;
			}
			while (i <= right)
			{
				merged.push_back((*Array)[i++]);
				(*swaping)++;
			}

			for (i=left; i <= right; i++)
			{
				(*Array)[i] = merged[i - left];
				(*swaping)++;
			}
		}

		void mergeSorting(int* swaping, int* comparisons, std::vector<int>* Array, int left, int right)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);
			assert(Array != nullptr);

			if (left < right)
			{
				(*comparisons)++;
				const int middile = (left + right) / 2;
				mergeSorting(swaping, comparisons, Array, left, middile);
				mergeSorting(swaping, comparisons, Array, middile+1, right);
				merge(swaping, comparisons, Array, left, middile, right);
			}
		}
		\endcode
	*/
	void mergeSorting(int* swaping, int* comparisons, std::vector<int>* Array, int left, int right)
	{
		assert(swaping != nullptr);
		assert(comparisons != nullptr);
		assert(swaping != comparisons);
		assert(Array != nullptr);

		if (left < right)
		{
			(*comparisons)++;
			const int middile = (left + right) / 2;
			mergeSorting(swaping, comparisons, Array, left, middile);
			mergeSorting(swaping, comparisons, Array, middile+1, right);
			merge(swaping, comparisons, Array, left, middile, right);
		}
	}

	//! \brief   Быстрая сортировка
	//!
	//! \param[out] swaping			число обменов
	//! \param[out] comparisons		число сравнений
	//! \param[out] Array			сортеруемый массив
	//! \param left					начало сортируемого участка
	//! \param right				конец сортируемого участка
	/*! Код функции выглядит следующим образом :
		\code
		void quickSorting(int* swaping, int* comparisons, std::vector<int>* Array, int left, int right)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);
			assert(Array != nullptr);

			if (right - left <= 0)
				return;

			int p = left;
			for (int i = left; i < right-1; i++)
				if ((*Array)[i] < (*Array)[right - 1])
				{
					(*comparisons)++;
					std::swap((*Array)[p], (*Array)[i]);
					(*swaping)++;
					p++;
				}
			std::swap((*Array)[p], (*Array)[right - 1]);
			quickSorting(swaping, comparisons, Array, left, p);
			quickSorting(swaping, comparisons, Array, p + 1, right);
		}
		\endcode
	*/
	void quickSorting(int* swaping, int* comparisons, std::vector<int>* Array, int left, int right)
	{
		assert(swaping != nullptr);
		assert(comparisons != nullptr);
		assert(swaping != comparisons);
		assert(Array != nullptr);

		if (right - left <= 0)
			return;

		int p = left;
		for (int i = left; i < right-1; i++)
			if ((*Array)[i] < (*Array)[right - 1])
			{
				(*comparisons)++;
				std::swap((*Array)[p], (*Array)[i]);
				(*swaping)++;
				p++;
			}
		std::swap((*Array)[p], (*Array)[right - 1]);
		quickSorting(swaping, comparisons, Array, left, p);
		quickSorting(swaping, comparisons, Array, p + 1, right);
	}

	//! \brief   Сортировка выбором
	//!
	//! \param[out] swaping			число обменов
	//! \param[out] comparisons		число сравнений
	//! \param[out] Array			сортеруемый массив
	//! \param n					число элементов для сортировки от 0
	/*! Код функции выглядит следующим образом :
		\code
		void selcetionSorting(int* swaping, int* comparisons, std::vector<int>* Array, int n)
		{
			assert(swaping != nullptr);
			assert(comparisons != nullptr);
			assert(swaping != comparisons);
			assert(Array != nullptr);

			for (int i = 0; i < n; i++)
			{
				int min = (*Array)[i];
				int index = i;
				for(int j = i+1; j<n;j++)
					if (min > (*Array)[j])
					{
						(*comparisons)++;
						min = (*Array)[j];
						index = j;
					}
				std::swap((*Array)[i], (*Array)[index]);
				(*swaping)++;
			}
		}
		\endcode
	*/
	void selcetionSorting(int* swaping, int* comparisons, std::vector<int>* Array, int n)
	{
		assert(swaping != nullptr);
		assert(comparisons != nullptr);
		assert(swaping != comparisons);
		assert(Array != nullptr);

		for (int i = 0; i < n; i++)
		{
			int min = (*Array)[i];
			int index = i;
			for(int j = i+1; j<n;j++)
				if (min > (*Array)[j])
				{
					(*comparisons)++;
					min = (*Array)[j];
					index = j;
				}
			std::swap((*Array)[i], (*Array)[index]);
			(*swaping)++;
		}
	}

//=================================================================================================================

	void GetResultOfAccount(int* swaping, int* comparisons, std::vector<int>mainArray, std::string nameFunction, int n)
	{
		assert(swaping != nullptr);
		assert(comparisons != nullptr);
		assert(swaping != comparisons);

		if (nameFunction == "Heap")
		{
			heap<int>Heap;
			Heap.heap_sort(swaping, comparisons, &mainArray, n);
			return;
		}
		if (nameFunction == "Insertion")
		{
			insertionSorting(swaping, comparisons, &mainArray, n);
			return;
		}
		if (nameFunction == "Bubble")
		{
			bubleSorting(swaping, comparisons, &mainArray, n);
			return;
		}
		if (nameFunction == "Merge")
		{
			mergeSorting(swaping, comparisons, &mainArray, 0, n-1);
			return;
		}
		if (nameFunction == "Quick")
		{
			quickSorting(swaping, comparisons, &mainArray, 0, n);
			return;
		}
		if (nameFunction == "Selection")
		{
			selcetionSorting(swaping, comparisons, &mainArray, n);
			return;
		}
	}
}