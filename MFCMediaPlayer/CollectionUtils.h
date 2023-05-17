#pragma once

#include <stddef.h>
#include <string.h>

template <class Atn> class CCollectionTempt
{
public:
	void mfn_Flush();       // deallocate list
	void mfn_Swap(Atn*,Atn*);   // swap two records
	void mfn_Del(Atn*);       // delete entry from list
	long mfn_Count();       // count entryes
	Atn* mfn_Insert(Atn*);
	Atn* mfn_Add(Atn *);         // add element to list (get pointer to new element)
	void mfn_AddRec(Atn*);    // add element to list (create new element and insert specified data)
	Atn* mfn_GetHead();
	Atn* mfn_GetTail();
	Atn* mfn_GetItem(int);  // get item i from list -- return null if not there  (RMF added)
	void mfn_Cpy(Atn* ptmdest,Atn* ptmsrc);   // copy src to dest
	void mfn_Sort(int(*compare)(Atn* ptma, Atn* ptmb)); // bubble-sort list

	CCollectionTempt(void);     // default constructor
	~CCollectionTempt(void);    // default destructor
	Atn*   m_ptrtmHead;
	Atn*   m_ptrtmTail;

protected:
	long m_lCount;
};

template<class Atn>
CCollectionTempt<Atn>::CCollectionTempt(void)
{
	m_ptrtmHead=m_ptrtmTail=NULL;
	m_lCount=0;
};

template<class Atn>
Atn* CCollectionTempt<Atn>::mfn_GetHead(void)
{
	return(m_ptrtmHead);
};

template<class Atn>
long CCollectionTempt<Atn>::mfn_Count()
{
	return(m_lCount);
};

template<class Atn>
Atn* CCollectionTempt<Atn>::mfn_GetTail(void)
{
	return(m_ptrtmTail);
};

template<class Atn>             // default destructor frees the list
CCollectionTempt<Atn>::~CCollectionTempt(void)
{
	mfn_Flush();
};

template<class Atn>
Atn* CCollectionTempt<Atn>::mfn_Add(Atn *l_ptrtmInfo)
{
	//Atn *l_ptrtmInfo; //,S_INFO;
	l_ptrtmInfo=new(Atn);
	ZeroMemory(l_ptrtmInfo,sizeof(Atn));
	if (l_ptrtmInfo==NULL)	
		return(NULL);

	ZeroMemory(l_ptrtmInfo,sizeof(Atn));   // give all data fields a known state

	if (m_ptrtmHead != NULL)	{          // update head and tail pointers	
		m_ptrtmTail->m_ptrNext=l_ptrtmInfo;
		l_ptrtmInfo->m_ptrPrev=m_ptrtmTail;
		m_ptrtmTail=l_ptrtmInfo;
		m_ptrtmTail->m_ptrNext=NULL;
	} 
	else	{
		m_ptrtmHead=l_ptrtmInfo;
		m_ptrtmHead->m_ptrNext=NULL;
		m_ptrtmTail=m_ptrtmHead;
		m_ptrtmHead->m_ptrPrev=NULL;
	}
	m_lCount++;
	return(l_ptrtmInfo);     // return a pointer of the template type
};

template<class Atn>
void CCollectionTempt<Atn>::mfn_AddRec(Atn* pptrtmData)
{
	Atn *l_ptrtmNewItem;
	l_ptrtmNewItem = mfn_Add();
	mfn_Cpy(l_ptrtmNewItem, pptrtmData);
}

template<class Atn>
Atn* CCollectionTempt<Atn>::mfn_Insert(Atn* pptrtmCurrent)
{
	Atn *l_ptrtmInfo; //,S_INFO;
	if (pptrtmCurrent==NULL)
		return NULL;

	// allocate new record
	l_ptrtmInfo=new(Atn);
	if (l_ptrtmInfo==NULL)
		return(NULL);

	// insert new record  before current
	if (pptrtmCurrent->m_ptrPrev)
		pptrtmCurrent->m_ptrPrev->m_ptrNext = l_ptrtmInfo;
	else
		m_ptrtmHead = l_ptrtmInfo;
	
	l_ptrtmInfo->m_ptrPrev = pptrtmCurrent->m_ptrPrev;
	pptrtmCurrent->m_ptrPrev = l_ptrtmInfo;
	l_ptrtmInfo->m_ptrNext = pptrtmCurrent;
	m_lCount++;
	return(l_ptrtmInfo);     // return a pointer of the template type
};

template <class Atn>
void CCollectionTempt<Atn>::mfn_Flush()
{
	Atn* l_ptrtmA;
	Atn* l_ptrtmB;
	l_ptrtmA=m_ptrtmHead;
	while (l_ptrtmA)	{
		l_ptrtmB=l_ptrtmA;         // windows uses the 386 processors MMU
		l_ptrtmA=l_ptrtmA->m_ptrNext;   // so get the next pointer before the CPU kills it
		delete(l_ptrtmB);   // or the VMM page is swapped
		l_ptrtmB = NULL;
	}
	m_ptrtmHead=NULL;
	m_ptrtmTail=NULL;
	m_lCount=0;
}


template <class Atn>
void CCollectionTempt<Atn>::mfn_Swap(Atn* pptrtmP1,Atn* pptrtmP2)
{
	Atn *l_ptrtmTemp = new Atn;
	Atn* l_ptrtmP;

	memcpy(l_ptrtmTemp,pptrtmP1,sizeof(Atn));
	memcpy(pptrtmP1,pptrtmP2,sizeof(Atn));
	memcpy(pptrtmP2,l_ptrtmTemp,sizeof(Atn));

	l_ptrtmP        = pptrtmP1->m_ptrNext;
	pptrtmP1->m_ptrNext  = pptrtmP2->m_ptrNext;
	pptrtmP2->m_ptrNext  = l_ptrtmP;

	l_ptrtmP        = pptrtmP1->m_ptrPrev;
	pptrtmP1->m_ptrPrev  = pptrtmP2->m_ptrPrev;
	pptrtmP2->m_ptrPrev  = (Atn*) l_ptrtmP;

	// prevent inline destructor from
	// deallocation strings
	memset(l_ptrtmTemp,NULL,sizeof(Atn));
	delete l_ptrtmTemp;
}

template <class Atn>
void CCollectionTempt<Atn>::mfn_Del(Atn* pptrtmInfo)
{
	_try	{
		if (pptrtmInfo==NULL)
			return;

		if (pptrtmInfo->m_ptrPrev!=NULL && pptrtmInfo->m_ptrNext!=NULL)	{
			pptrtmInfo->m_ptrPrev->m_ptrNext=pptrtmInfo->m_ptrNext;
			pptrtmInfo->m_ptrNext->m_ptrPrev=pptrtmInfo->m_ptrPrev;
			delete(pptrtmInfo);
			pptrtmInfo = NULL;
			m_lCount--;
		} 
		else if (pptrtmInfo->m_ptrPrev==NULL && pptrtmInfo->m_ptrNext!=NULL)	{
			m_ptrtmHead=pptrtmInfo->m_ptrNext;
			pptrtmInfo->m_ptrNext->m_ptrPrev=NULL;
			pptrtmInfo->m_ptrNext=NULL;
			pptrtmInfo->m_ptrPrev=NULL;
			delete(pptrtmInfo);
			pptrtmInfo = NULL;
			m_lCount--;
		} 
		else if (pptrtmInfo->m_ptrPrev!=NULL && pptrtmInfo->m_ptrNext==NULL)	{
			m_ptrtmTail=pptrtmInfo->m_ptrPrev;
			pptrtmInfo->m_ptrPrev->m_ptrNext=NULL;
			pptrtmInfo->m_ptrNext=NULL;
			pptrtmInfo->m_ptrPrev=NULL;
			delete(pptrtmInfo);
			pptrtmInfo = NULL;
			m_lCount--;
		} 
		else if (pptrtmInfo->m_ptrPrev==NULL && pptrtmInfo->m_ptrNext==NULL)	{
			m_ptrtmTail=NULL;
			m_ptrtmHead=NULL;
			delete(pptrtmInfo);
			pptrtmInfo = NULL;
			m_lCount--;
		}
	}
	__except(1){}
}

//added getitem   (4/29/99 rmf)
template<class Atn>
Atn* CCollectionTempt<Atn>::mfn_GetItem(int piItem)
{
	Atn *l_ptrtmInfo;
	int l_iCounter = 1;

	l_ptrtmInfo = m_ptrtmHead;

	while(l_ptrtmInfo && l_iCounter < piItem)	{
		l_ptrtmInfo = l_ptrtmInfo->m_ptrNext;
		l_iCounter++;
	}

	return(l_ptrtmInfo);
}


template <class Atn>
void CCollectionTempt<Atn>::mfn_Cpy(Atn* pptrtmDest,Atn* pptrtmSrc)
{
	// Only want to copy the data portion of <Atn> that is not
	// related to the link list. So save copies of *m_ptrPrev and *m_ptrNext
	Atn* l_ptrtmPrev;
	Atn* l_ptrtmNext;
	l_ptrtmPrev = pptrtmDest->m_ptrPrev;
	l_ptrtmNext = pptrtmDest->m_ptrNext;          

	memcpy(pptrtmDest,pptrtmSrc,sizeof(Atn));

	// Restore *m_ptrPrev and *m_ptrNext
	pptrtmDest->m_ptrPrev = l_ptrtmPrev;
	pptrtmDest->m_ptrNext = l_ptrtmNext;          
}


// bubble-sort list
template <class Atn>
void CCollectionTempt<Atn>::mfn_Sort(int(*compare)(Atn* pptrtmA, Atn* pptrtmB))
{
	if(mfn_Count() < 2)
		return;

	Atn* l_ptrtmT1  = mfn_GetHead();
	Atn* l_ptrtmT2  = GetTail();

	do	{
		int l_iNextLoop = 0;
		if(l_ptrtmT1->m_ptrNext == l_ptrtmT2)
			l_iNextLoop = 1;

		if(compare(l_ptrtmT1, l_ptrtmT1->m_ptrNext) > 0)
			swap(l_ptrtmT1, l_ptrtmT1->m_ptrNext);
		else	{
			if(l_iNextLoop == 1)
				l_ptrtmT2 = l_ptrtmT1;
			else
				l_ptrtmT1 = l_ptrtmT1->m_ptrNext;
		}

		if(l_iNextLoop == 1)
			l_ptrtmT2 = mfn_GetHead();
	}while(l_ptrtmT2 != mfn_GetHead());
}



