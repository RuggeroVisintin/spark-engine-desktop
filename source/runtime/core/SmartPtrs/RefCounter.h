#ifndef _REFCOUNTER_
#define _REFCOUNTER_

namespace SE
{
	namespace core
	{
		namespace memory
		{
			// this class is intended to count the number of references to the object 
			class RefCounter
			{
			private:
				int m_ref_count;

			public:
				RefCounter() 
					: m_ref_count(0) 
				{
				}

				virtual ~RefCounter() {
					m_ref_count = 0;
				}

			public:
				void reference() {
					m_ref_count++;
				}

				void deReference() {
					if (m_ref_count > 0)
						m_ref_count--;
				}

				int refCount() {
					return m_ref_count;
				}
			};
		}
	}
}

#endif // !_REFCOUNTER_