/******************************************************************\
* TableLoader - �������� ������ �� ��������� ������. ������ 1.7    *
\******************************************************************/
#ifndef TableLoaderH
#define TableLoaderH

struct TLSection
{
	String *Name;
	int Pos;	//������� ������ � 0
	int Size;//���-�� �����
};

class TableLoader
{
private:
   char *FFormat;
	//Mem ����������� [Count][FRowCount]
	String **MemStr;
   int **MemInt;
	Char **MemChar;
   bool **MemBool;
	int StrCount, IntCount, CharCount, BoolCount;
   int FRowCount;
	int FColCount;

protected:    
	TLSection *FSections;
   void SectionEnsureCapacity(int count);
   int SectionCapacity;
	int FSectionCount;
	void Load(TStringList *list, const char *format);
	int RealGetSection(int SectionIdx, va_list &args);

public:     
	__fastcall TableLoader();
	__property char* Format = {read = FFormat};
	__property int RowCount = {read = FRowCount};
	__property int ColCount = {read = FColCount};
	__property int SectionCount = {read = FSectionCount};
	__property TLSection* Sections = {read = FSections};
	TLSection* FindSection(String SectionName);
	bool IgnoreFirstString; //������������ ������ ����� � �����. defaul=true
	bool IgnoreDelimitersPack; //������������ �����������, ������ ������. defauly=true
	Char Delimiter;      //����������� �������� (���������)
   String EndMark; 		//"[end]"
	//��������, format: i-int c-Char s-String b-bool, ... ������ ������ �� ����������
	int LoadFromFile(String Filename, const char *format, ...);
	int LoadFromResource(String ResourceName, const char *format, ...);
	int LoadFromList(TStrings *list, const char *format, ...);
	//GetSection: ... ��� ������ ������, ����� ��� � LoadFrom. ���������� ���-�� ����� � ������
	int GetSection(const String SectionName="", ...);
	//RegColumn - ������������� ������ �� ������� � ������. ColNum - ����� ������� ����� ����. ���������� ���-�� ����� � ������
	int RegColumn(int* &Field, int ColNum, const String SectionName = "") const;
	int RegColumn(Char* &Field, int ColNum, const String SectionName = "") const;
	int RegColumn(String* &Field, int ColNum, const String SectionName = "") const;
	int RegColumn(bool* &Field, int ColNum, const String SectionName = "") const;
	void GetCount(int &intCount, int &charCount, int &boolCount, int &strCount) const;
	void Clear();
	__fastcall ~TableLoader() { Clear(); };
};

#endif
