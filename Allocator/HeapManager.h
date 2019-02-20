#pragma once

#include <Windows.h>
#include <set>
#include <map>
#include <vector>


//��������� ��� �������� ��������� ��������

struct CMemorySegment {
	char* prev{0};
	char* dataPointer{0};
	int size{0};
	bool isBusy{false};

	CMemorySegment() = default;
	CMemorySegment(char* prev,
		char* dataPointer,
		int size,
		bool isBusy);
};


//�������� ��������� ��� ������ �� ������ 
bool operator<( const CMemorySegment& first, const CMemorySegment& second );



//-------------------------------------------------------------------------------------------------


//���������� ��� ������ �� ����������

class CMemoryPointerCompartor {
public:
	bool operator()(const CMemorySegment& first, const CMemorySegment& second) const;
};


//-------------------------------------------------------------------------------------------------


//���������

class HeapManager {
public:
	// max_size - ������ ������������������ ������� ������ ��� ��������
	// min_size - ������ �������������� ������� ��� ��������
	HeapManager( int min_size, int max_size );
	// ��� ������ ������ ���� ����������� ����� ��������� ������
	~HeapManager();
	
	// ������������ ������ ������� size
	void* Alloc( int size );
	// ���������� ������
	void Free( void* ptr );

private:
	int pageSize{4096};
	int maxSize{4096};
	int minSize{1024};
	char* dataPointer{0};
	std::set<CMemorySegment> freeSegments;
	std::map<char* , CMemorySegment> allSegments;
	std::set<char*> busyPointers;

	std::vector<char> isCommited;

	int roundValue( int value ) const;
	char* tryGetPointer( int size );
	void decommitPages( const CMemorySegment& memorySegment );
};
