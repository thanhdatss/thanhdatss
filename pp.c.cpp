#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct struct_birthday
{
	float day;
	float month;
	float year;
};

typedef struct struct_birthday BIRTHDAY;

struct contact
{
	char first_name[25];
	char last_name[25];
	char company[50];
	char phone_number[25];
	char email[50];
	char working_address[50];
	char home_address[50];
	BIRTHDAY birthday;
};


typedef struct contact CT;


void print_menu();
void add_contact(CT *list, int *top);
void edit_contact(CT *list, int top);
void delete_contact(CT *list, int *top);  
void search_contact(CT *list, int top);  
void list_all_contacts_with_birthdays_in_a_given_month(CT *list, int top); 
void list_all_contacts_in_the_table_format(CT *list, int top); 
void export_to_file(CT *list, int top);
void update_from_file1( int *top, FILE *f);
void update_from_file2(CT *list, int *top, FILE *f);
void add_contact_information(CT *sample);
void add_phone_number(CT *sample);
void add_birthday(CT *sample);
void display_information(CT sample);
int location(CT *list, int top);
void clear();


int main()
{	
	int top = -1;   
	FILE *f;
	char choice;
	 
	CT *list;
	list = (CT *)malloc( sizeof(CT));
	
	if(list == NULL)
	{
		printf("Cannot be allocated");
		exit(0);
	}
	
	do
	{
		system("cls"); 
		print_menu();
		scanf("%c%*c", &choice);

	
		system("cls"); 

		printf("CONTACT KEEPER\n");
		printf("==============\n\n");
	

		switch(choice)
		{
			case '1':
				list = (CT *)realloc(list, (top+2)*sizeof(CT));	
				add_contact(list, &top);
				break;
			case '2':
				edit_contact(list, top);
				break;
			case '3':
				delete_contact(list, &top);
				list = (CT *)realloc(list, (top + 1)*sizeof(CT));
				break;
			case '4':
				search_contact(list, top);
				break;
			case '5' :
				list_all_contacts_with_birthdays_in_a_given_month(list, top);
				break;
			case '6' :
				list_all_contacts_in_the_table_format(list, top);
				break;
			case '7' :
				export_to_file(list, top);
				break;
			case '8' :
				update_from_file1(&top, f);
				
				char name_file[100];
				printf("\nEnter name file: ");
				scanf("%s", name_file); clear();
				
				f = fopen(name_file, "rb");
				fread(&top, sizeof(int), 1, f);
				
				list = (CT *)realloc(list, (top + 1)*sizeof(CT));
				update_from_file2(list, &top, f);
				break;
		}		
		
		
		if (choice != 'q')
		{	
			printf("\n\n---\n");
			printf("Press any key to back to main menu.");
			getchar();
			clear();
		}
	}
	while (choice != 'q');

	free(list);
	return 0;
}


void print_menu()
{
	printf("CONTACT KEEPER\n");
	printf("==============\n\n");
	printf("1. Add Contact\n");
	printf("2. Edit Contact\n");
	printf("3. Delete Contact\n");
	printf("4. Search_contact\n");
	printf("5. List all contacts with birthdays in a given month\n");
	printf("6. List all contacts in the table format\n");
	printf("7. export to file\n");
	printf("8. update from file\n");
	printf("q. Quit\n\n");
	printf("Enter your choice (1/2/3/4/5/6/7/8/q): ");
}


void add_contact(CT *list, int *top)
{
	CT sample;	
	
	*top = *top + 1;
	
	if((list+ *top)==NULL)
	{
		printf("Cannot be allocated");
		return;
	}
	
	add_contact_information(&sample);	
	list[*top] = sample;
	
	printf("You added successfully");
}


void edit_contact(CT *list, int top)
{
	int loc = location(list, top);
	
	if(loc == -1)
		printf("Not contact found");
	else
		{
			printf("\nStart editing:\n\n");
			add_contact_information(&list[loc]);
		}
	
}


void delete_contact(CT *list, int *top)
{	
	int i, loc;   // loc = location
	
	printf("Choose 1/2 to delete\n");
	
	loc = location(list, *top);

	if(loc == -1)
		printf("Not contact found");
	else
	{	
		for(i = loc; i <= *top; i++)
			{	
				list[i] = list[i+1];
			}
			
		*top = *top - 1;
		
		printf("You deleted successfully");		
	}	
}


void search_contact(CT *list, int top)
{
	int loc;  // loc = location
	
	printf("Choose 1/2 to search\n");
	
	loc = location(list, top);
	
	if(loc == -1 )
		printf("Not contact found");
	else
	{
	printf("\n\nInformation: \n\n");
	display_information(list[loc]);
	}
}


void list_all_contacts_with_birthdays_in_a_given_month(CT *list, int top)
{	
	int i, j, x = 1;
	float month;
	
	printf("Enter the birth month of the contacts you want to show: "); scanf("%f", &month); clear();
	
	for(i = 0; i <= top; i++)
	{
		for(j = i; j <= top; j++)
			{
				if(list[i].birthday.day > list[j].birthday.day )
				{
					CT temp = list[i];
					list[i] = list[j];
					list[j] = temp;
				}		
			}
	}
	
	printf("\nList of all contact that same a month(%.0f) of birth: \n\n", month);
	
	for(i = 0; i <= top; i++)
	{	
		if(list[i].birthday.month == month )	
		{
		printf("Information of contact %d: \n", i+1); 
		display_information(list[i]);
		}
	}
	
}


void list_all_contacts_in_the_table_format(CT *list, int top)
{
	int i, j, x;
	
	
	for(i = 0; i < top; i++)
	{
		for(j = 0; j < top - i; j++)
		{	
		
		
			if(strcmp(list[j].first_name, list[j+1].first_name) > 0)
			{
				CT temp = list[j];
					list[j] = list[j+1];
					list[j+1] = temp;
			}
		}
	}
	
	for(i = 0; i <= top; i++)
	{	
		printf("Information of contact %d: \n", i+1);
		display_information(list[i]);
	}
}


void export_to_file(CT *list, int top)
{
	char name_file[100];
	printf("\nEnter name file: ");
	scanf("%s", name_file); clear();
	
	FILE *f2;
	f2 = fopen(name_file, "wb");
	
	if(f2==NULL){
		printf("\nError");
		return;
	}
	
	fwrite(&top, sizeof(top), 1, f2);
	for(int i = 0; i <= top; i++)
	{
		fwrite(&list[i], sizeof(CT), 1, f2);
	}
	
	printf("successfully");
	
	fclose(f2);	
}


void update_from_file1( int *top, FILE *f)
{

}
void update_from_file2(CT *list, int *top, FILE *f)
{	
	for(int i = 0; i <= *top; i++)
	{
		fread(&list[i], sizeof(CT), 1, f);
	}
	
	printf("successfully");
	
	fclose(f);	
}


void add_contact_information(CT *sample)
{
	printf("Enter first name: "); fgets(sample->first_name, sizeof(sample->first_name), stdin);
	if(sample->first_name[0] >= 97 && sample->first_name[0] <= 122)
		sample->first_name[0] = sample->first_name[0] - 32;
	
	printf("Enter last name: "); fgets(sample->last_name, sizeof(sample->last_name), stdin);
	if(sample->last_name[0] >= 97 && sample->last_name[0] <= 122)
		sample->last_name[0] = sample->last_name[0] - 32;
	
	printf("Enter company: "); fgets(sample->company, sizeof(sample->company), stdin);
	add_phone_number(sample);
	printf("Enter email: "); fgets(sample->email, sizeof(sample->email), stdin);
	printf("Enter working address: "); fgets(sample->working_address, sizeof(sample->working_address), stdin);
	printf("Enter home address: "); fgets(sample->home_address, sizeof(sample->home_address), stdin);
	add_birthday(sample);
}


void add_birthday(CT *sample)
{
	BIRTHDAY B;  
	int check;
	
	printf("Birthday(DD/MM/YYYY):\n");
	
	do
	{	
		check = 0;
		
		printf("Enter day: "); scanf("%f", &B.day); clear();
		printf("Enter month: "); scanf("%f", &B.month); clear();
		printf("Enter year: "); scanf("%f", &B.year); clear();
		 
		if(B.month == 1 || B.month == 3 || B.month == 5 || B.month == 7 || B.month == 8 || B.month == 10 || B.month == 12)
		{
			if(B.day > 31 || B.day < 1 )
				check = 1;
		}
		
		else if(B.month == 4 || B.month == 6 || B.month == 9 || B.month == 11)
		{
			if(B.day > 30 || B.day < 1)
				check = 1;
		}
		
		else if(B.month == 2)
		{
			if((int)B.year % 400 == 0 || ((int)B.year % 4 == 0 && (int)B.year % 100 != 0))
			{
				if(B.day > 29 || B.day < 1)
					check = 1;
			}
			else
				if(B.day > 28 || B.day < 1)
					check = 1;
				
		}
		
		else
			check = 1;
		
		
		if(check == 1)
		{
			printf("ERROR, Bithday should be in the DD/MM/YYYY format \n");
			printf("Re-Enter\n");
		}
	}
	while(check == 1);
	
	sample->birthday = B;
}


void add_phone_number(CT *sample)
{
	int len, i, check;
	
	printf("Enter phone number( Phone Number should be a number of 9 or 10 digits): ");
	
	do
	{
		check = 0;
		
		fgets(sample->phone_number, sizeof(sample->phone_number), stdin);
		len = strlen(sample->phone_number) - 1;
		
		for(i = 0; i <= 8; i++)
		{
			if(sample->phone_number[i] < 48 || sample->phone_number[i] > 57)
				check = 1;
		}
		
		if(len == 10 && (sample->phone_number[9] < 48 || sample->phone_number[9] > 57 ))
			check = 1;
			
		if(len > 10)
			check = 1;
					
		if(check == 1)
		{	
       		printf("ERROR, Phone Number should be a number of 9 or 10 digits\n");
 			printf("Re-enter phone number: ");
		}
	}
	while(check == 1);
}


void display_information(CT sample)
{
	printf("First name: %s", sample.first_name); 
	printf("Last name: %s", sample.last_name); 
	printf("Company: %s", sample.company);
	printf("Phone number: %s", sample.phone_number);
	printf("Email: %s", sample.email);
	printf("Working address: %s", sample.working_address); 
	printf("Home address: %s", sample.home_address);
	printf("Birthday: %02.0f/%02.0f/%04.0f\n\n\n", sample.birthday.day, sample.birthday.month, sample.birthday.year);
}


int location(CT *list, int top)
{	
	char choice;
	int i;
	CT sample;
	
	printf("1. Perform operation with name\n");
	printf("2. Perform operation with phone number\n\n");
	printf("Enter your choice (1/2): ");
	scanf("%c", &choice);
	clear();
	
	if(choice == '1')
	{
		printf("Enter first name: "); fgets(sample.first_name, sizeof(sample.first_name), stdin);
		if(sample.first_name[0] >= 97 && sample.first_name[0] <= 122)
			sample.first_name[0] = sample.first_name[0] - 32;
		
		printf("Enter last name: "); fgets(sample.last_name, sizeof(sample.last_name), stdin);
		if(sample.last_name[0] >= 97 && sample.last_name[0] <= 122)
			sample.last_name[0] = sample.last_name[0] - 32;
		
		
		for(i = 0; i <= top; i++)
		{		
			if(strcmp(sample.first_name, list[i].first_name) == 0 && strcmp(sample.last_name, list[i].last_name) == 0)
				return i;
		}
		
		return -1;
	}
	
	else if(choice == '2')
	{
		add_phone_number(&sample);
		for(i = 0; i <= top; i++)
		{	
			if(strcmp(sample.phone_number, list[i].phone_number) == 0)
				return i;
		}
		
		return -1;
	}
	else
		return -1;      
}


void clear()
{
	char c;
	
	do
	{
		scanf("%c", &c);
	}
	while(c != '\n');
}
