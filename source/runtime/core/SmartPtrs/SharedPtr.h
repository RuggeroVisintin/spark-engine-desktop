#ifndef __SHAREDPTR_H__
#define __SHAREDPTR_H__

#include "RefCounter.h"

namespace SE
{
	namespace core
	{
		namespace memory
		{
			template <class T> class SharedPtr
			{
			private:
				T*				m_shared;
				RefCounter*		m_ref_counter;

			public:
				SharedPtr()
				{
					m_shared = 0;
					m_ref_counter = new RefCounter();
				}

				SharedPtr(T* object)
				{
					m_shared = object;
					m_ref_counter = new RefCounter();

					m_ref_counter->reference();
				}

				SharedPtr(const SharedPtr<T>& shared_ptr)
				{
					assign(shared_ptr);
				}

				~SharedPtr()
				{
					release();
				}

			public:
				T& operator* () const { return *m_shared; }
				T* operator-> () const { return m_shared; }
				SharedPtr<T>& operator=(const SharedPtr<T>& sharedPtr);

				void	reset();
				void 	reset(const SharedPtr<T>& shared_ptr);

				int 	useCount() const;
				void 	swap(SharedPtr<T>& shared_ptr);
				void 	assign(const SharedPtr<T>& sharedPtr);

			private:
				void release();
			};

			template <class T>
			SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& sharedPtr)
			{
				reset(sharedPtr);
				return *this;
			}

			template <class T>
			void SharedPtr<T>::reset()
			{
				release();
			}

			template <class T>
			void SharedPtr<T>::reset(const SharedPtr<T>& sharedPtr)
			{
				if (m_shared != sharedPtr.m_shared) {

					release();
					assign(sharedPtr);
				}
			}

			template <class T>
			int SharedPtr<T>::useCount() const
			{
				return m_ref_counter->refCount();
			}

			template <class T>
			void SharedPtr<T>::swap(SharedPtr<T>& sharedPtr)
			{
				if (sharedPtr.m_shared != m_shared) {
					SharedPtr<T> temp = *this;
					*this = sharedPtr;
					sharedPtr = temp;
				}
			}

			template <class T>
			void SharedPtr<T>::assign(const SharedPtr<T>& sharedPtr)
			{
				m_shared = sharedPtr.m_shared;
				m_ref_counter = sharedPtr.m_ref_counter;

				m_ref_counter->reference();
			}

			template <class T>
			void SharedPtr<T>::release()
			{
				if (m_ref_counter != 0) {
					m_ref_counter->deReference();

					if (m_ref_counter->refCount() == 0) {
						delete m_ref_counter;
						delete m_shared;
					}

					m_ref_counter = 0;
					m_shared = 0;
				}

			}
		}
	}
}

#endif // !__SHAREDPTR_H__