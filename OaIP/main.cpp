#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>



std::string fileName;
int curAmountOfStructs = 0;

enum Status
{
	LAUNCHED,
	STOPED,
};

enum SortBy : int
{
	VISITS_PER_DAY = 1,
	NAME = 2,
	EXIT = 3
};


struct Site
{
	union StructNumber
	{
		int structNumber ;
	};


	std::string name;
	std::string URL;
	std::string description;
	Status status;
	int visits;
	StructNumber number;
};



std::fstream CreateBinaryFile()
{
	std::fstream file("C:\\rep\\OaIP\\OaIP\\data.bin",
		std::fstream::binary | std::fstream::trunc | std::fstream::out);
	
	if (!file.is_open())
	{
		std::cout << "Failed to open bin file" << std::endl;
	}
	return file;
}


std::fstream CreateIndexFile()
{
	std::fstream file("C:\\rep\\OaIP\\OaIP\\index.ind",
		std::fstream::trunc | std::fstream::out);

	if (!file.is_open())
	{
		std::cout << "Failed to open index file" << std::endl;
	}
	return file;
}

std::fstream CreateTextFile()
{
	std::fstream file("C:\\rep\\OaIP\\OaIP\\data.txt", 
					  std::fstream::trunc | std::fstream::out);

	if (!file.is_open())
	{
		std::cout << "Failed to open text file" << std::endl;
	}
	return file;
}


bool GetFileTypeFromUser(std::fstream &file)
{
	int input;
	std::cout << "Выберите тип файла для хранения данных" << std::endl;
	std::cout << "1. Бинарный" << std::endl;
	std::cout << "2. Текстовый" << std::endl;
	std::cin >> input;

	if (input == 1)
	{
		file = CreateBinaryFile();
		return true;
	}
	else if (input == 2)
	{
		file = CreateTextFile();
		return true;
	}
	else
	{
		return false;
	}
}


void ReWriteT(Site* arrOfSites, std::fstream &file,int size)
{
	file.close();

	file.open(fileName, std::ios::out | std::ios::trunc);
	file << curAmountOfStructs << std::endl;

		for (int i = 0; i < curAmountOfStructs; ++i)
		{
			file << arrOfSites[i].name << std::endl;
			file << arrOfSites[i].URL << std::endl;
			file << arrOfSites[i].description << std::endl;
			file << arrOfSites[i].visits << std::endl;
			file << arrOfSites[i].status << std::endl;
			file << arrOfSites[i].number.structNumber << std::endl;
		}
	file.close();
}

void ReWriteB(Site* arrOfSites, std::fstream& file, int size)
{
	file.close();

	file.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary);

	file.write((char*)&curAmountOfStructs, sizeof(curAmountOfStructs));
	for (int i = 0; i < curAmountOfStructs; ++i)
	{
		file.write((char*)&arrOfSites[i], sizeof(Site));
	}

	file.close();
	file.open(fileName,std::ios::binary | std::ios::in);
}


void ReWriteIndexFile(std::fstream& indexFile)
{
	
}

void SortStructByVisits(Site* arr, int size,std::fstream &file)
{
	Site temp;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size-1; ++j)
		{
			if(arr[j].visits > arr[j+1].visits)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			
		}
	}
	if(fileName == "C:\\rep\\OaIP\\OaIP\\data.txt")
		ReWriteT(arr, file, size);

	if (fileName == "C:\\rep\\OaIP\\OaIP\\data.bin")
		ReWriteB(arr, file, size);


}


Status isSiteWorking()
{
	
L1:
	char a;
	std::cin >> a;

	if (a == 'y')
	{
		return LAUNCHED;
	}
	else if (a  == 'n')
	{
		return STOPED;
	}
	else
	{
		std::cout << "Неверный символ, попробуйте ещё раз" << std::endl;
		goto L1;
	}
}


void MostVisitingSite(Site* arr, int size)
{
	Site a = arr[0];

	for (int i = 1; i < size; ++i)
	{
		if (arr[i].visits > a.visits)
		{
			a = arr[i];
		}
	}

	std::cout << "Найболее посещаемый сайт - " << a.name << std::endl;

}


void FillStructT(Site* temp, std::fstream& file, const int amounOfStructs)
{
	curAmountOfStructs = amounOfStructs;
	file << curAmountOfStructs << std::endl;

	for (int i = 0; i < amounOfStructs; ++i)
	{
		std::cout << "Введите имя сайта" << std::endl;
		std::cin >> temp[i].name;
		file << temp[i].name << std::endl;


		std::cout << "Введите URL сайта" << std::endl;
		std::cin >> temp[i].URL;
		file << temp[i].URL << std::endl;

		std::cout << "Введите краткое описание сайта" << std::endl;
		std::cin >> temp[i].description;
		file << temp[i].description << std::endl;

		std::cout << "Введите URL количество посещений в день" << std::endl;
		std::cin >> temp[i].visits;
		file << temp[i].visits << std::endl;

		std::cout << "Сайт сейчас работает y/n" << std::endl;
		temp[i].status = isSiteWorking();
		file << temp[i].status << std::endl;


		temp[i].number.structNumber = i;
		file << temp[i].number.structNumber << std::endl;
	}
}


void FillStructB(Site* temp, std::fstream& file, const int amounOfStructs)
{
	curAmountOfStructs = amounOfStructs;

	for (int i = 0; i < amounOfStructs; ++i)
	{
		std::cout << "Введите имя сайта" << std::endl;
		std::cin >> temp[i].name;

		std::cout << "Введите URL сайта" << std::endl;
		std::cin >> temp[i].URL;

		std::cout << "Введите краткое описание сайта" << std::endl;
		std::cin >> temp[i].description;

		std::cout << "Введите URL количество посещений в день" << std::endl;
		std::cin >> temp[i].visits;

		std::cout << "Сайт сейчас работает y/n" << std::endl;
		temp[i].status = isSiteWorking();


		temp[i].number.structNumber = i;
	}
	ReWriteB(temp, file, curAmountOfStructs);
}


Site* CompleteStruct(Site* arrOfSites,std::fstream& file,Site*temp)
{
	int counter = 0;
	int amountOfStructs;

	std::cout << "Введите количество структур" << std::endl;
	std::cin >> amountOfStructs;

	curAmountOfStructs += amountOfStructs;


	temp = new Site[curAmountOfStructs];

	for (int i = 0; i < curAmountOfStructs-amountOfStructs; i++)
	{
		temp[i].description = arrOfSites[i].description;
		temp[i].name = arrOfSites[i].name;
		temp[i].number = arrOfSites[i].number;
		temp[i].status = arrOfSites[i].status;
		temp[i].URL = arrOfSites[i].URL;
		temp[i].visits = arrOfSites[i].visits;
		counter++;
	}

	
	
	for (int i = curAmountOfStructs- amountOfStructs; i < curAmountOfStructs; ++i)
	{
		std::cout << "Введите имя сайта" << std::endl;
		std::cin >> temp[i].name;


		std::cout << "Введите URL сайта" << std::endl;
		std::cin >> temp[i].URL;

		std::cout << "Введите краткое описание сайта" << std::endl;
		std::cin >> temp[i].description;

		std::cout << "Введите URL количество посещений в день" << std::endl;
		std::cin >> temp[i].visits;

		std::cout << "Сайт сейчас работает y/n" << std::endl;
		temp[i].status = isSiteWorking();
		counter++;

		temp[i].number.structNumber = counter;
	}

	if (fileName == "C:\\rep\\OaIP\\OaIP\\data.txt")
		ReWriteT(temp, file, curAmountOfStructs);

	if (fileName == "C:\\rep\\OaIP\\OaIP\\data.bin")
		ReWriteB(temp, file, curAmountOfStructs);

	return temp;

}


void AddNewField(Site* arrOfSites, std::fstream& file)
{
	Site* temp = nullptr;
	arrOfSites = CompleteStruct(arrOfSites, file, temp);
	delete[] temp;
}


Site* GetDataFromFileB(std::fstream& file)	// Bin Files
{
	file.open("C:\\rep\\OaIP\\OaIP\\data.bin", std::ios::binary | std::ios::in);
	;
	int amountOfStructs;
	int sizeOfNextValue;

	file.read((char*)&amountOfStructs, sizeof(curAmountOfStructs));
	
	curAmountOfStructs = amountOfStructs;

	Site* arrOfSites = new Site[amountOfStructs];

	for (int i = 0; i < curAmountOfStructs; ++i)
	{
		file.read((char*)&arrOfSites[i], sizeof(Site));
	}
	return arrOfSites;
}

Site* GetDataFromFileT(std::fstream &file)	// Text Files
{
	std::string strBuff;
	file.open("C:\\rep\\OaIP\\OaIP\\data.txt");

	getline(file, strBuff, '\n');
	int amountOfStructs = std::stol(strBuff);
	curAmountOfStructs = amountOfStructs;
	Site *arrOfSites = new Site[amountOfStructs];

	for (int i = 0; i < amountOfStructs; ++i)
	{
		getline(file, strBuff, '\n');
		arrOfSites[i].name = strBuff;
		getline(file, strBuff, '\n');
		arrOfSites[i].URL = strBuff;
		getline(file, strBuff, '\n');
		arrOfSites[i].description = strBuff;
		getline(file, strBuff, '\n');
		arrOfSites[i].visits = std::stoi(strBuff);
		getline(file, strBuff, '\n');
		arrOfSites[i].status = static_cast<Status>(std::stoi(strBuff));
		getline(file, strBuff, '\n');
		arrOfSites[i].number.structNumber = std::stoi(strBuff);
	}

	return arrOfSites;
}

void PrintStruct(Site* arr, int size, std::fstream& file)  //Do not touch
{
	file.close();

	if (fileName == "C:\\rep\\OaIP\\OaIP\\data.txt")
		arr = GetDataFromFileT(file);

	if (fileName == "C:\\rep\\OaIP\\OaIP\\data.bin")
		arr = GetDataFromFileB(file);

	for (int i = 0; i < size; i++)
	{
		std::cout << "Имя сайта :" << arr[i].name << std::endl;
		std::cout << "URL :" << arr[i].URL << std::endl;
		std::cout << "Описание :" << arr[i].description << std::endl;
		std::cout << "Количество посещений :" << arr[i].visits << std::endl;

		std::cout << "Состояние сайта :";
		if (arr[i].status == LAUNCHED)
			std::cout << "Запущен" << std::endl;
		else
			std::cout << "Остановлен" << std::endl;

		std::cout << std::endl;
	}

}
void DeleteField(Site* arrOfSites, std::fstream& file) // Fix or delete
{
	
	file.close();

	if (fileName == "C:\\rep\\OaIP\\OaIP\\data.txt")
		arrOfSites = GetDataFromFileT(file);

	if (fileName == "C:\\rep\\OaIP\\OaIP\\data.bin")
		arrOfSites = GetDataFromFileB(file);

	std::string str;
	std::cout << "Введите имя поля для удаления" << std::endl;

	std::cin >> str;


	for (int i = 0; i < curAmountOfStructs; i++)
	{
		if (arrOfSites[i].name == str)
		{
			Site* temp = new Site[curAmountOfStructs - 1];
			for (int j = 0; j < curAmountOfStructs - 1; ++j)
			{
				if (i != j)
				{
					temp[j].name = arrOfSites[j].name;
					temp[j].description = arrOfSites[j].description;
					temp[j].URL = arrOfSites[j].URL;
					temp[j].visits = arrOfSites[j].visits;
					temp[j].status = arrOfSites[j].status;
					temp[j].number.structNumber = arrOfSites[j].number.structNumber;
				}
				
			}
			curAmountOfStructs--;
			if (fileName == "C:\\rep\\OaIP\\OaIP\\data.txt")
				ReWriteT(temp, file, curAmountOfStructs);

			if (fileName == "C:\\rep\\OaIP\\OaIP\\data.bin")
				ReWriteB(temp, file, curAmountOfStructs);
		}
	}
}


void SortFileByIndexByName(std::fstream& indexFile)
{

}


void SortFileByIndexByVisits(std::fstream& indexFile)
{


}


void SortFileByIndexM(std::fstream& indexFile)
{
	std::cout << "Выберите по какому полю сортировать данные" << std::endl;
	std::cout << "1. Сортировать по количеству посещений" << std::endl;
	std::cout << "2. Сортировать по имени" << std::endl;
	std::cout << "3. Назад" << std::endl;


	int action;
	std::cin >> action;
	
	if (static_cast<SortBy>(action) == SortBy::VISITS_PER_DAY)
	{
		SortFileByIndexByVisits(indexFile);
	}
	if (static_cast<SortBy>(action) == SortBy::NAME)
	{
		SortFileByIndexByName(indexFile);
	}
	if (static_cast<SortBy>(action) == SortBy::EXIT)
	{
		// Do nothing and func return to main loop
	}
	else
	{
		std::cout << "Неверный символ, попробуйте ёще раз" << std::endl;
		SortFileByIndexM(indexFile);
	}
}


// Постфикс T - текстовый файл
//          B - бинарный файл

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Site* arrOfSites = nullptr;
	int amountOfStructs = 0;
	bool isRunning = true;
	std::fstream file;
	std::fstream indexFile;

	if (!std::filesystem::exists("C:\\rep\\OaIP\\OaIP\\index.ind"))
	{
		indexFile = CreateIndexFile();
	}
	indexFile.open("C:\\rep\\OaIP\\OaIP\\index.ind", std::ios::in);

	if (!std::filesystem::exists("C:\\rep\\OaIP\\OaIP\\data.txt") &&
		!std::filesystem::exists("C:\\rep\\OaIP\\OaIP\\data.bin"))
	{
		if (!GetFileTypeFromUser(file))
		{
			std::cout << "Неверный символ, попробуйте ещё раз" << std::endl;
			GetFileTypeFromUser(file);
		}
		std::cout << "Введите количество структур" << std::endl;
		std::cin >> amountOfStructs;
		arrOfSites = new Site[amountOfStructs];
		if (std::filesystem::exists("C:\\rep\\OaIP\\OaIP\\data.txt"))
		{
			FillStructT(arrOfSites, file, amountOfStructs);
			fileName = "C:\\rep\\OaIP\\OaIP\\data.txt";

		}
		if (std::filesystem::exists("C:\\rep\\OaIP\\OaIP\\data.bin"))
		{
			fileName = "C:\\rep\\OaIP\\OaIP\\data.bin";
			FillStructB(arrOfSites, file, amountOfStructs);
		}
	}
	else
	{
		if (std::filesystem::exists("C:\\rep\\OaIP\\OaIP\\data.txt"))
		{
			arrOfSites = GetDataFromFileT(file);
			fileName = "C:\\rep\\OaIP\\OaIP\\data.txt";
		}
		if (std::filesystem::exists("C:\\rep\\OaIP\\OaIP\\data.bin"))
		{
			arrOfSites = GetDataFromFileB(file);
			fileName = "C:\\rep\\OaIP\\OaIP\\data.bin";

		}
	}


	while (isRunning == true)
	{
		int action;
		std::cout << "Выберите действие:" << std::endl;
		std::cout << "1. Отсортировать массив по количеству посещений" << std::endl;
		std::cout << "2. Вывести содержимое массива" << std::endl;
		std::cout << "3. Вывести самый посещаемый сайт" << std::endl;
		std::cout << "4. Добавить новое поле" << std::endl;
		std::cout << "5. Удалить поле" << std::endl;
		std::cout << "6. Сортировка по индексному файлу" << std::endl;
		std::cout << "7. Выйти" << std::endl;

		std::cin >> action;

		switch (action)
		{
		case 1:
		{
			SortStructByVisits(arrOfSites, curAmountOfStructs,file);
			break;
		}
		case 2:
		{
			PrintStruct(arrOfSites, curAmountOfStructs,file);
			break;
		}
		case 3:
		{
			MostVisitingSite(arrOfSites, curAmountOfStructs);
			break;
		}
		case 4:
		{
			AddNewField(arrOfSites, file);
			break;
		}
		case 5:
		{
			DeleteField(arrOfSites,file);
			break;
		}
		case 6:
		{
			SortFileByIndexM(indexFile);
			break;
		}
		case 7:
		{
			isRunning = false;
			break;
		}
		default:
			break;
		}

	}

}
	
