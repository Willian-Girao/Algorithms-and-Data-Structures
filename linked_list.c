#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double dvdComis(int tvDVD)
{
	double comis = 0.0;

	if (tvDVD < 10)
	{
		comis = tvDVD * 20.0;
	} else {
		comis = 9 * 20.0;
		comis += (tvDVD - 9) * 30.0;
	}

	return comis;
}

double tvComis(int tv)
{
	double comis = 0.0;

	if (tv < 15)
	{
		comis = tv * 10.0;
	} else {
		comis = 14 * 10.0;
		comis += (tv - 14) * 15.0;
	}

	return comis;
}

struct Employees
{
	int inscriptionNumber, tvDVD, tv;
	double tvDVDComis, tvComis, rawSalary, liquidSalary, deductions;
	struct Employees *next;
};

struct Employees *head = NULL;

void inserEmployee(int a, int b, int c, double fixedSalary, double inssDiscount)
{
	double otherDiscount = 0.0;

	struct Employees *temp = (struct Employees*) malloc(sizeof(struct Employees));
	
	temp->inscriptionNumber = a;
	temp->tvDVD = b;
	temp->tv = c;

	temp->tvDVDComis = dvdComis(b);
	temp->tvComis = tvComis(c);
	temp->rawSalary = fixedSalary + temp->tvDVDComis + temp->tvComis;

	if ((temp->rawSalary - inssDiscount) >= 1000)
	{
		otherDiscount = ((temp->rawSalary - inssDiscount) * 5.0) / 100.0;
	}

	temp->deductions = inssDiscount + otherDiscount;

	temp->liquidSalary = temp->rawSalary - temp->deductions;
	
	temp->next = head;

	head = temp;
}

void printList() {
   struct Employees *ptr = head;

   printf("\n\nLISTA DE FUNCIONARIOS\n\n");	
   
   while(ptr != NULL)
   {
   	printf("# Inscricao: %d\n", ptr->inscriptionNumber);
	printf("Salario bruto: R$ %lf\n", ptr->rawSalary);
	printf("Deducoes: R$ %lf\n", ptr->deductions);
	printf("Salario liquido: R$ %lf\n\n", ptr->liquidSalary);

	ptr = ptr->next;
   }
}

int main()
{
	int employeesNumber, a, b, c;
	double fixedSalary;

	printf("Quantidade de funcionarios: ");
	scanf("%d", &employeesNumber);

	printf("Salario fixo: ");
	scanf("%lf", &fixedSalary);

	double inssDiscount = (fixedSalary * 8.0) / 100.0;

	for (int i = 0; i < employeesNumber; ++i)
	{
		printf("\n# de inscricao: ");
		scanf("%d", &a);
		printf("# TV/DVD: ");
		scanf("%d", &b);
		printf("# TV: ");
		scanf("%d", &c);

		inserEmployee(a, b, c, fixedSalary, inssDiscount);
	}

	printList();


	return 0;
}
