
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <direct.h>
#include <conio.h>

constexpr auto dictionary = "dictionary.bin";
constexpr auto folder = "‪D";

struct word
{
	char eng[30] = {};
	char ukr[30] = {};

	void set_Eng()
	{
		std::cout << "ENG : ";
		std::cin >> this->eng; 
	}

	void set_Ukr()
	{
		std::cout << "UKR : ";
		std::cin >> this->ukr;
	}

	void save_word()
	{
		FILE* file = fopen(dictionary, "a+b");
		fwrite(this, sizeof(word), 1, file);
		fclose(file);
	}

	bool read_word(int n)
	{
		FILE* file = fopen(dictionary, "r+b");
		if (file != 0)
			fopen(dictionary, "a+b");

		if (file != 0)
			fseek(file, (n - 1) * sizeof(word) * 1L, SEEK_SET);
		
		if (!fread(this, sizeof(word), 1, file))
		{
			fclose(file);
			return false;
		}

		fclose(file);
		return true;
	}

	char* set_path() 
	{
		char path[40] = {};
		strcat(path, folder);
		strcat(path, "\\");
		strcat(path, this->eng);
		strcat(path, ".txt");
		return path;
	}

	bool is_repeated()
	{
		char path[40] = {};
		strcpy(path, this->set_path());

		FILE* file = fopen(path, "r+");
		char temp[30] = {};
		unsigned int count = 0; 

		while (!feof(file) && count < 29)
		{
			temp[count] = fgetc(file);
			if (temp[count] == '\n') 
			{
				temp[count] = '\0';
				count = -1;
				if (!strcmp(temp, this->ukr))
				{
					fclose(file);
					return true;
				}
			}
			count++;
 			temp[count] = '\0';
		}
		fclose(file);
		return false;
	}

	void write_file()
	{
		char path[40] = {};
		strcpy(path, this->set_path());

		FILE* file = fopen(path, "a+");

		if (file != 0)
			fclose(file);

		if (this->is_repeated())
			return;

		file = fopen(path, "a+");

		fputs(this->ukr, file);
		fputc('\n', file);

		fclose(file);
	}
};

void set_words()
{

	word word;

	bool isDone = false;
	
	while (!isDone)
	{
		system("cls");
		std::cout << "Enter the word : \n";          
		word.set_Eng();
		word.set_Ukr();
		word.save_word();
		std::cout << "One more? (press 1)\n";
		switch (_getch())
		{
		case 49:
			break;
		default:
			isDone = true;
			break;
		}
	}
}

void add_words()
{
	word word;

	int i = 1;
	while (word.read_word(i++))
	{
		word.write_file();
	}
}

int main()
{
	system("chcp 1251");
	system("cls");

	if (_mkdir(folder));

	while (1)
	{
		system("cls");
		std::cout << "Add new words to the dictionary -> enter\nSave them into the folder`s files from dictionary -> space\nExit -> esc";
		int choice = 0;
		bool isAnswered = false;
		while (!isAnswered)
		{
			choice = _getch();
			switch (choice)
			{
			case 13:
				system("cls");
				set_words();
				isAnswered = true;
				break;
			case 27:
				return 0;
				break;
			case 32:
				system("cls");
				add_words();
				isAnswered = true;
				break;
			default:
				break;
			}
		}
		std::cout << "Done!" << std::endl;
		system("pause");
	}
}