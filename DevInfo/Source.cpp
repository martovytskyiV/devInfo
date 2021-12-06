#include <windows.h>
#include <iostream>
#include <Lmcons.h>
using namespace std;
#pragma comment(lib, "user32.lib")

int main()
{
	/*1) GetLogicalDrives

	Функция GetLogicalDrives возвращает число - битовую маску в которой храняться все
		доступные диски.

		DWORD GetLogicalDrives(VOID);

	Параметры:
		Эта функция не имеет параметров.

		Возвращаемое значение :
	Если функция вызвана правильно, то она возвращает число - битовую маску в которой
		храняться все доступные диски(если 0 бит равен 1, то диск "A:" присутствует, и т.д.)
		Если функция вызвана не правильно, то она возвращает 0.*/

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
	Функция GetDriveType возвращает тип диска(removable, fixed, CD - ROM,
		RAM disk, или network drive).


		UINT GetDriveType(LPCTSTR lpRootPathName);

		Параметры:
			lpRootPathName

				[in] Указатель на не нулевую стоку в которой хранится имя
				главной директории на диске.Обратный слэш должен присутствовать!
				Если lpRootPathName равно NULL, то функция использует текущую директорию.

		Возвращаемое значение :
				Функция возвращает тип диска.Могут быть следующие значения :

						Значение					Описание
					DRIVE_UNKNOWN 					Не известный тип.
					DRIVE_NO_ROOT_DIR				Не правильный путь.
					DRIVE_REMOVABLE					Съёмный диск.
					DRIVE_FIXED						Фиксированный диск.
					DRIVE_REMOTE					Удалённый или network диск.
					DRIVE_CDROM						CD - ROM диск.
					DRIVE_RAMDISK					RAM диск.*/

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

	//Функция GetVolumeInformation возвращает информацию о файловой системе и
	//	дисках(директориях).

	//	BOOL GetVolumeInformation(
	//		LPCTSTR lpRootPathName,           // имя диска(директории)           [in]
	//		LPTSTR lpVolumeNameBuffer,        // название диска                  [out]
	//		DWORD nVolumeNameSize,            // длина буфера названия диска     [in] 
	//		LPDWORD lpVolumeSerialNumber,     // сериальный номер диска          [out]
	//		LPDWORD lpMaximumComponentLength, // максимальная длина фыйла        [out]
	//		LPDWORD lpFileSystemFlags,        // опции файловой системы          [out]
	//		LPTSTR lpFileSystemNameBuffer,    // имя файловой системы            [out]
	//		DWORD nFileSystemNameSize         // длина буфера имени файл. сист.  [in]
	//	);

	//Возвращаемое значение :
	//Если функция вызвана правильно, то она возвращает не нулевое значение(TRUE).
	//	Если функция вызвана не правильно, то она возвращает 0(FALSE).
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

	//Функция GetDiskFreeSpaceEx выдаёт информацию о доступном месте на диске.

	//	BOOL GetDiskFreeSpaceEx(
	//		LPCTSTR lpDirectoryName,                 // имя диска(директории)            [in]
	//		PULARGE_INTEGER lpFreeBytesAvailable,    // доступно для использования(байт) [out]
	//		PULARGE_INTEGER lpTotalNumberOfBytes,    // максимальный объём( в байтах )   [out]
	//		PULARGE_INTEGER lpTotalNumberOfFreeBytes // свободно на диске( в байтах )    [out]
	//	);

	//Возвращаемое значение :
	//Если функция вызвана правильно, то она возвращает не нулевое значение(TRUE).
	//	Если функция вызвана не правильно, то она возвращает 0(FALSE).
	
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

	//Функция GlobalMemoryStatus возвращает информацию о используемой системой памяти.

	//	VOID GlobalMemoryStatus(
	//		LPMEMORYSTATUS lpBuffer   // указатель на структуру MEMORYSTATUS
	//	);

	//typedef struct _MEMORYSTATUS {
	//	DWORD dwLength;                  // длина структуры в байтах
	//	DWORD dwMemoryLoad; 		 // загрузка памяти в процентах		
	//	SIZE_T dwTotalPhys;              // максимальное количество физической памяти в байтах
	//	SIZE_T dwAvailPhys;              // свободное количество физической памяти в байтах
	//	SIZE_T dwTotalPageFile;          // макс. кол. памяти для программ в байтах
	//	SIZE_T dwAvailPageFile;          // свободное кол. памяти для программ в байтах
	//	SIZE_T dwTotalVirtual;           // максимальное количество виртуальной памяти в байтах
	//	SIZE_T dwAvailVirtual; 		 // свободное количество виртуальной памяти в байтах
	//} MEMORYSTATUS, * LPMEMORYSTATUS;

	//Возвращаемое значение :
	//Эта функция не возвращает параметров
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

	//Функция GetComputerName возвращает NetBIOS имя локального компьютера.

	//	BOOL GetComputerName(
	//		LPTSTR lpBuffer,  // имя локального компьютера( длина буфера равна MAX_COMPUTERNAME_LENGTH + 1 ) [out]
	//		LPDWORD lpnSize   // размер буфера ( лучше поставить MAX_COMPUTERNAME_LENGTH + 1 )               [out/in] 
	//	);

	//Функция GetUserName возвращает имя текущего узера.

	//	BOOL GetUserName(
	//		LPTSTR lpBuffer,  // имя юзера( длина буфера равна UNLEN + 1 )   [out]
	//		LPDWORD nSize     // размер буфера ( лучше поставить UNLEN + 1 ) [out/in] 
	//	);

	//Возвращаемые значения :
	//Если функции вызваны правильно, то они возвращают не нулевое значение(TRUE).
	//	Если функции вызваны не правильно, то они возвращают 0(FALSE).
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