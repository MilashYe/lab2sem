#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
using namespace std;
const int number = 5;

struct list
{
	char name[100] = {};
	int marks[number];
	double krasauchik;
};

int DONE(FILE* , list *);

void AVERAGE(list * , int );

void OUT(list *, int );

int main()
{
	setlocale(LC_ALL, "Ukr");
	int n;
	FILE *file = fopen("students.csv", "r+");
	fscanf(file, "%d\n", &n);
	struct list *student = new list[n];
	int counter = DONE(file, student);
	fclose(file);
	AVERAGE(student, counter);
	sort(student, student + counter, [](struct list& _student1, struct list& _student2)
	{ return _student1.krasauchik > _student2.krasauchik; });

	OUT(student, counter);

	double a = counter*0.4;
	int b = (int)a - 1;

	cout << "Minimalnyy bal dlya stipuhen = " << student[b].krasauchik << endl;

	delete[] student;

	return 0;
}

int DONE(FILE* file, list *student)
{
	char str[100] = {};
	int counter = 0;
	char reyt[number][number - 1] = {};
	char kontract[6] = {};
	while (!feof(file))
	{
		fgets(str, 100, file);

            for (int i = 0;i < 100;i++)
            {
			if (str[i] == '_')
			{
				str[i] = '0';
			}
            }

		char *strin = strtok(str, ",\n");
		int nomer = -1;
		while (strin != 0)
		{
			if (nomer == -1)
			{
				strcpy(student[counter].name, strin);
				nomer++;
			}
			else if (nomer < number)
			{
				strcpy(reyt[nomer], strin);
				nomer++;
			}
			else { strcpy(kontract, strin); }
			strin = strtok(0, ",\n");
		}
		if ( strcmp(kontract, "FALSE") == 0 || kontract[0]==NULL)
		{
			for (int i = 0; i < number; i++)
			{
				student[counter].marks[i] = atoi(reyt[i]);
			}
			++counter;
		}
	}
	return counter;
}
void AVERAGE(list * student, int counter)
{
	for_each(student, student + counter, [](struct list& file)
	{
		file.krasauchik = 0;
		for (int i = 0; i < number; i++)
		{
			file.krasauchik += file.marks[i];
		}
		file.krasauchik /= number;
	});
}
void OUT(list *student, int counter)
{
	FILE *out = fopen("rating.csv", "w");
	for (int i = 0; i < counter*0.4 - 1; i++)
	{
		fprintf(out, "%s,%.3f\n\n", student[i].name, student[i].krasauchik);
	}
	fclose(out);
}
