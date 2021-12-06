#include <windows.h>
#include <iostream>
#include <Lmcons.h>
using namespace std;
#pragma comment(lib, "user32.lib")

int main()
{
	/*1) GetLogicalDrives

	������� GetLogicalDrives ���������� ����� - ������� ����� � ������� ��������� ���
		��������� �����.

		DWORD GetLogicalDrives(VOID);

	���������:
		��� ������� �� ����� ����������.

		������������ �������� :
	���� ������� ������� ���������, �� ��� ���������� ����� - ������� ����� � �������
		��������� ��� ��������� �����(���� 0 ��� ����� 1, �� ���� "A:" ������������, � �.�.)
		���� ������� ������� �� ���������, �� ��� ���������� 0.*/

	int n;
	char dd[4];
	DWORD dr = GetLogicalDrives();

	for (int i = 0; i < 26; i++)
	{
		n = ((dr >> i) & 0x00000001);
		if (n == 1)
		{
			dd[0] = char(65 + i); dd[1] = ':'; dd[2] = '\\'; dd[3] = 0;
			cout << "Available disk drives : " << dd << endl;
		}
	}
//----------------------------------------------------------------------------
	/*2) GetDriveType
	������� GetDriveType ���������� ��� �����(removable, fixed, CD - ROM,
		RAM disk, ��� network drive).


		UINT GetDriveType(LPCTSTR lpRootPathName);

		���������:
			lpRootPathName

				[in] ��������� �� �� ������� ����� � ������� �������� ���
				������� ���������� �� �����.�������� ���� ������ ��������������!
				���� lpRootPathName ����� NULL, �� ������� ���������� ������� ����������.

		������������ �������� :
				������� ���������� ��� �����.����� ���� ��������� �������� :

						��������					��������
					DRIVE_UNKNOWN 					�� ��������� ���.
					DRIVE_NO_ROOT_DIR				�� ���������� ����.
					DRIVE_REMOVABLE					������� ����.
					DRIVE_FIXED						������������� ����.
					DRIVE_REMOTE					�������� ��� network ����.
					DRIVE_CDROM						CD - ROM ����.
					DRIVE_RAMDISK					RAM ����.*/

	int d;

	d = GetDriveType(L"C:\\");
	cout << "C:\\ : ";
	if (d == DRIVE_UNKNOWN) cout << " UNKNOWN" << endl;
	if (d == DRIVE_NO_ROOT_DIR) cout << " DRIVE NO ROOT DIR" << endl;
	if (d == DRIVE_REMOVABLE) cout << " REMOVABLE" << endl;
	if (d == DRIVE_FIXED) cout << " FIXED" << endl;
	if (d == DRIVE_REMOTE) cout << " REMOTE" << endl;
	if (d == DRIVE_CDROM) cout << " CDROM" << endl;
	if (d == DRIVE_RAMDISK) cout << " RAMDISK" << endl;
//----------------------------------------------------------------------------
	//3) GetVolumeInformation

	//������� GetVolumeInformation ���������� ���������� � �������� ������� �
	//	������(�����������).

	//	BOOL GetVolumeInformation(
	//		LPCTSTR lpRootPathName,           // ��� �����(����������)           [in]
	//		LPTSTR lpVolumeNameBuffer,        // �������� �����                  [out]
	//		DWORD nVolumeNameSize,            // ����� ������ �������� �����     [in] 
	//		LPDWORD lpVolumeSerialNumber,     // ���������� ����� �����          [out]
	//		LPDWORD lpMaximumComponentLength, // ������������ ����� �����        [out]
	//		LPDWORD lpFileSystemFlags,        // ����� �������� �������          [out]
	//		LPTSTR lpFileSystemNameBuffer,    // ��� �������� �������            [out]
	//		DWORD nFileSystemNameSize         // ����� ������ ����� ����. ����.  [in]
	//	);

	//������������ �������� :
	//���� ������� ������� ���������, �� ��� ���������� �� ������� ��������(TRUE).
	//	���� ������� ������� �� ���������, �� ��� ���������� 0(FALSE).
	char VolumeNameBuffer[100];
	char FileSystemNameBuffer[100];
	unsigned long VolumeSerialNumber;

	BOOL GetVolumeInformationFlag = GetVolumeInformationA(
		"c:\\",
		VolumeNameBuffer,
		100,
		&VolumeSerialNumber,
		NULL, //&MaximumComponentLength,
		NULL, //&FileSystemFlags,
		FileSystemNameBuffer,
		100
	);

	if (GetVolumeInformationFlag != 0)
	{
		cout << "	Volume Name is " << VolumeNameBuffer << endl;
		cout << "	Volume Serial Number is " << VolumeSerialNumber << endl;
		cout << "	File System is " << FileSystemNameBuffer << endl;
	}
	else cout << "	Not Present (GetVolumeInformation)" << endl;
//----------------------------------------------------------------------------
	//4) GetDiskFreeSpaceEx

	//������� GetDiskFreeSpaceEx ����� ���������� � ��������� ����� �� �����.

	//	BOOL GetDiskFreeSpaceEx(
	//		LPCTSTR lpDirectoryName,                 // ��� �����(����������)            [in]
	//		PULARGE_INTEGER lpFreeBytesAvailable,    // �������� ��� �������������(����) [out]
	//		PULARGE_INTEGER lpTotalNumberOfBytes,    // ������������ �����( � ������ )   [out]
	//		PULARGE_INTEGER lpTotalNumberOfFreeBytes // �������� �� �����( � ������ )    [out]
	//	);

	//������������ �������� :
	//���� ������� ������� ���������, �� ��� ���������� �� ������� ��������(TRUE).
	//	���� ������� ������� �� ���������, �� ��� ���������� 0(FALSE).
	
	DWORD FreeBytesAvailable;
	DWORD TotalNumberOfBytes;
	DWORD TotalNumberOfFreeBytes;

	BOOL GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx(
		L"c:\\",					  // directory name
		(PULARGE_INTEGER)&FreeBytesAvailable,     // bytes available to caller
		(PULARGE_INTEGER)&TotalNumberOfBytes,     // bytes on disk
		(PULARGE_INTEGER)&TotalNumberOfFreeBytes  // free bytes on disk
	);

	if (GetDiskFreeSpaceFlag != 0)
	{
		cout << "	Total Number Of Free Bytes = " << (unsigned )TotalNumberOfFreeBytes
			<< "( " << unsigned (TotalNumberOfFreeBytes) / 1024 / 1000
			<< " Mb )" << endl;
		cout << "	Total Number Of Bytes = " << (unsigned long)TotalNumberOfBytes
			<< "( " << unsigned long(TotalNumberOfBytes) / 1024 / 1000
			<< " Mb )" << endl;
	}
	else	cout << "	Not Present (GetDiskFreeSpace)" << endl;
	
	//----------------------------------------------------------------------------
	//5) GlobalMemoryStatus

	//������� GlobalMemoryStatus ���������� ���������� � ������������ �������� ������.

	//	VOID GlobalMemoryStatus(
	//		LPMEMORYSTATUS lpBuffer   // ��������� �� ��������� MEMORYSTATUS
	//	);

	//typedef struct _MEMORYSTATUS {
	//	DWORD dwLength;                  // ����� ��������� � ������
	//	DWORD dwMemoryLoad; 		 // �������� ������ � ���������		
	//	SIZE_T dwTotalPhys;              // ������������ ���������� ���������� ������ � ������
	//	SIZE_T dwAvailPhys;              // ��������� ���������� ���������� ������ � ������
	//	SIZE_T dwTotalPageFile;          // ����. ���. ������ ��� �������� � ������
	//	SIZE_T dwAvailPageFile;          // ��������� ���. ������ ��� �������� � ������
	//	SIZE_T dwTotalVirtual;           // ������������ ���������� ����������� ������ � ������
	//	SIZE_T dwAvailVirtual; 		 // ��������� ���������� ����������� ������ � ������
	//} MEMORYSTATUS, * LPMEMORYSTATUS;

	//������������ �������� :
	//��� ������� �� ���������� ����������
	//  The MemoryStatus structure is 32 bytes long.
	//  It should be 32.
	//  78 percent of memory is in use.
	//  There are   65076 total Kbytes of physical memory.
	//  There are   13756 free Kbytes of physical memory.
	//  There are  150960 total Kbytes of paging file.
	//  There are   87816 free Kbytes of paging file.
	//  There are  1fff80 total Kbytes of virtual memory.
	//  There are  1fe770 free Kbytes of virtual memory.

#define DIV 1024
#define WIDTH 7
	char* divisor = (char*)"K";

	MEMORYSTATUSEX  stat;

	GlobalMemoryStatusEx(&stat);

	printf("There is  %*ld percent of memory in use.\n",
		WIDTH, stat.dwMemoryLoad);
	printf("There are %*I64d total KB of physical memory.\n",
		WIDTH, stat.ullTotalPhys / DIV);
	printf("There are %*I64d free  KB of physical memory.\n",
		WIDTH, stat.ullAvailPhys / DIV);
	printf("There are %*I64d total KB of paging file.\n",
		WIDTH, stat.ullTotalPageFile / DIV);
	printf("There are %*I64d free  KB of paging file.\n",
		WIDTH, stat.ullAvailPageFile / DIV);
	printf(("There are %*I64d total KB of virtual memory.\n"),
		WIDTH, stat.ullTotalVirtual / DIV);
	printf("There are %*I64d free  KB of virtual memory.\n",
		WIDTH, stat.ullAvailVirtual / DIV);

	// Show the amount of extended memory available.

	printf("There are %*I64d free  KB of extended memory.\n",
		WIDTH, stat.ullAvailExtendedVirtual / DIV);
	//----------------------------------------------------------------------------

	//6) GetComputerName, GetUserNameA

	//������� GetComputerName ���������� NetBIOS ��� ���������� ����������.

	//	BOOL GetComputerName(
	//		LPTSTR lpBuffer,  // ��� ���������� ����������( ����� ������ ����� MAX_COMPUTERNAME_LENGTH + 1 ) [out]
	//		LPDWORD lpnSize   // ������ ������ ( ����� ��������� MAX_COMPUTERNAME_LENGTH + 1 )               [out/in] 
	//	);

	//������� GetUserName ���������� ��� �������� �����.

	//	BOOL GetUserName(
	//		LPTSTR lpBuffer,  // ��� �����( ����� ������ ����� UNLEN + 1 )   [out]
	//		LPDWORD nSize     // ������ ������ ( ����� ��������� UNLEN + 1 ) [out/in] 
	//	);

	//������������ �������� :
	//���� ������� ������� ���������, �� ��� ���������� �� ������� ��������(TRUE).
	//	���� ������� ������� �� ���������, �� ��� ���������� 0(FALSE).
	char ComputerName[32];
	unsigned long len_ComputerName = MAX_COMPUTERNAME_LENGTH + 1;
	char UserName[UNLEN + 1];
	unsigned long len_UserName = UNLEN + 1;


	BOOL comp = GetComputerName(
		(LPWSTR)ComputerName,
		&len_ComputerName
	);

	if (comp != 0) { cout << "Computer Name is " << ComputerName << endl; }
	else cout << "Computer Name is NOT FOUND !!! " << endl;

	comp = GetUserNameA(
		UserName,
		&len_UserName
	);

	if (comp != 0) { cout << "User Name is " << UserName << endl; }
	else cout << "User Name is NOT FOUND !!! " << endl;



	return 0;
}