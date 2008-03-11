#ifndef SMART_PTR_H
#define SMART_PTR_H

#if 0
	#define DEB(x) x
#else
	#define DEB(x)
#endif
#if 0
	#define DEB2(x) x
#else
	#define DEB2(x)
#endif

// #define CONFIG_USE_BOOST_POINTERS
#ifdef CONFIG_USE_BOOST_POINTERS

#include <boost/shared_ptr.hpp>
#define SmartPtr boost::shared_ptr
#define SmartPtrDelete(target)	void boost::checked_delete<target>(target* x);

#else

#define SmartPtrDelete(target)	class SmartPtr<target>

/**
 * The reference counting class
 */
class SmartPtrCount
{
	int m_refCount;

public:
	/**
	 * Construct a reference counting class for row pointer data
	 * \param data pointer
	 */
	SmartPtrCount()
		: m_refCount( 1 )
	{
		DEB( printf("SmartPtrCount ctor...\n"));
	}

	/**
	 * Destructor
	 */
	virtual ~SmartPtrCount()
	{
		DEB( printf("SmartPtrCount dtor...\n"));
	}

	/**
	 * Increase reference counting by 1
	 */
	void IncRef() { m_refCount ++ ; }

	/**
	 * Decrease reference counting by 1
	 */
	void DecRef() { m_refCount -- ; }
	/**
	 * Return the current reference counting
	 * \return current reference counting
	 */
	int  GetRefCount() { return m_refCount; }
};

/**
 * A smart pointer class that provides a reference counting and auto delete memory.
 *
 * This class is similar to std::auto_ptr, with 2 exceptions:
 * - This class uses reference counting
 * - We dont provide a release() function (because of the reference counting)
 * It is recommended to use this class instead of using raw pointer wherever possible.
 *
 * \note smart pointer to NULL is valid.
 */
template <class T>
class SmartPtr
{
	T* m_data;
	SmartPtrCount* m_ref;

public:
	/**
	 * Construct smart pointer from ptr
	 * \param ptr pointer
	 */
	SmartPtr(T* ptr)
	{
		DEB( printf("SmartPtr T* ctor...\n"));
		// create a fresh copy
		CreateFresh( ptr );
	}
	
	/**
	 * Default constructor
	 */
	SmartPtr()
		: m_data(NULL)
	{
		DEB( printf("SmartPtr ctor...\n"));
		m_ref = new SmartPtrCount();
	}

	/**
	 * Copy constructor
	 * \param rhs right hand side 
	 */
	SmartPtr(const SmartPtr& rhs)
		: m_data(NULL),
		m_ref(NULL)
	{
		DEB( printf("SmartPtr SmartPtr ctor...\n"));
		*this = rhs;
	}
	
	template<class Y>
	SmartPtr(SmartPtr<Y> const& rhs) 
		: m_data(rhs.m_data),
		m_ref(rhs.m_ref)
	{
		DEB( printf("SmartPtr SmartPtr<Y> ctor...\n"));
		m_ref->IncRef();
	}

	/**
	 * Assignment operator
	 * \param rhs right hand side 
	 * \return reference to this
	 */
	SmartPtr& operator=(const SmartPtr& rhs)
	{
		DEB2( printf("SmartPtr = operator...\n"));
		
		// increase the reference count
		if( m_ref == rhs.m_ref )
		{
			DEB2( printf("m_ref = rhs.m_ref\n") );
			return *this;
		}

		// Delete previous reference 
		DeleteRefCount();

		// TODO: What to do here?
		if( !rhs.m_ref )
		{
			DEB2( printf("!rhs.m_ref\n") );
			return *this;
		}
		
		DEB2( printf("no returns so far\n") );
		
		m_data = rhs.m_data;
		m_ref = rhs.m_ref;
		m_ref->IncRef();
		return *this;
	}

	/**
	 * Destructor
	 */
	virtual ~SmartPtr()
	{
		DEB( printf("SmartPtr dtor...\n"));
		DeleteRefCount();
	}

	/**
	 * Replace the current pointer with ptr
	 * if the current ptr is not NULL, it will be freed (reference counting free) before assingning the new ptr
	 * \param ptr new pointer
	 */
	void reset(T* ptr = 0)
	{	
		DeleteRefCount();
		CreateFresh( ptr );
	}

	/**
	 * Return pointer the row data pointer
	 * \return pointer to the row data pointer
	 */
	T* get() const
	{
		return m_data;
	}

	/**
	 * Overload the '->' operator 
	 * \return pointer to the row data pointer
	 */
	T* operator->() const 
	{
		return m_data;
	}

	/**
	 * Dereference operator
	 * \return dereference the row data
	 */
	T& operator*() const
	{
		return *(m_data);
	}

	/**
	 * Test for NULL operator
	 * \return true if the internal row data or the reference counting class are NULL false otherwise
	 */
	bool operator!() const
	{
		return (!m_ref || !m_data);
	}

	/**
	 * test for bool operation
	 * \return true of the internal raw data exist and it is not null
	 */
	operator bool() const
	{
		return m_ref && m_data;
	}
	
	void print() const
	{
		printf("%d: %p (%p)\n", m_ref->GetRefCount(), m_data, this);
	}

private:
	void DeleteRefCount()
	{
		DEB2( printf("DeleteRefCount()\n") );
		// decrease the ref count (or delete pointer if it is 1)
		if( m_ref )
		{
			DEB2( printf("m_ref\n") );
			if( m_ref->GetRefCount() <= 1 )
			{
				DEB2( printf("m_ref->GetRefCount() <= 1\n") );
				delete m_ref;
				m_ref = NULL;
				delete m_data;
				m_data = NULL;
			}
			else
			{
				DEB2( printf("m_ref->GetRefCount() = %d\n", m_ref->GetRefCount()) );
				m_ref->DecRef();
			}
		}
		else
		{
			DEB2( printf("!m_ref\n") );
		}
	};

	void CreateFresh(T* ptr)
	{
		m_ref = new SmartPtrCount();
		m_data = ptr;
	}
	
	template<class Y> friend class SmartPtr;
};

#endif // CONFIG_USE_BOOST_POINTERS
#endif // SMART_PTR_H
