// 1. We need to build a notebook to put peoples' phone numbers there
// it should work this way: first the program should ask person's name
// then if the name is correct (doesn't contain numbers, special characters, etc.)
// the program should ask for a phone number
// if the number is valid (contains + in the beginning, has proper amount of numbers - between 10 and 15)
// the program should put this data into some array.
// The program should be able to put multiple contacts in this array.
// 2. We should be able to get this data from the array somehow (up to you to decide).

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string string_tolower(string z);
bool contains(char a[], char b[]);
bool validate_number(char n[]);
void print_contact_info(int count);
int get_name_index(string name);
void edit_contact(int i);
string get_contact_name();
string get_contact_number();

string phonebook[100][2];
char invalid[] = "+*/=0123456789";
int count = 0;

int main (void)
{
    printf("Welcome to Phonebook!\n");
    while (true)
    {
        string name = get_contact_name();

        int name_index = get_name_index(name);
        if (name_index > -1)
        {
            printf("Contact found:\n");
            print_contact_info(name_index);
            edit_contact(name_index);
            continue;
        }

        string number = get_contact_number();

        phonebook[count][0] = name;
        phonebook[count][1] = number;
        count++;
    }
}

bool contains(char a[], char b[])
{
    for (int i = 0; i < strlen(b); i++)
    {
        if (strchr(a, b[i]) != NULL)
        {
            return true;
        }
    }

    return false;
}

bool validate_number(char n[])
{
    int j = strlen(n);
    if ((j >= 10 && j <= 15) && n[0] == '+')
    {
        for(int i = 1; i < j; i++)
        {
            if (n[i] < 48 || n[i] > 57)
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

void print_contact_info(int position)
{
    if (position < 0 || position >= sizeof(phonebook))
    {
        return;
    }

    string contact_name = phonebook[position][0];
    string contact_number = phonebook[position][1];
    printf("  %s\n  %s\n  #%i in the phonebook\n", contact_name, contact_number, position);
}

int get_name_index(string name)
{
    for (int i = 0, j = sizeof(phonebook); i < j; i++)
    {
        string contact_name = phonebook[i][0];
        if (contact_name == NULL)
            return -1;

        if (strcmp(string_tolower(contact_name), string_tolower(name)) == 0)
            return i;
    }

    return -1;
}

string string_tolower(string z)
{
    if (z == NULL)
        return z;

    int z_length = strlen(z);
    char *y = malloc(z_length + 1);
    strcpy(y, z);
    for (int i = 0; i < z_length; i++)
    {
        y[i] = tolower(y[i]);
    }
    
    y[z_length] = 0;
    return y;
}

void edit_contact(int name_index)
{
    while(true)
    {
        int answer = 0;
        do
        {
            answer = get_int("Do you want to edit something?\n  1 = edit name\n  2 = edit number \n  0 = nothing\n");
        }
        while(answer < 0 || answer > 2);

        switch(answer)
        {
            case 1:
                phonebook[name_index][0] = get_contact_name();
                break;
            case 2:
                phonebook[name_index][1] = get_contact_number();
                break;
            default:
                printf("Editing finished!\n");
                return;  
        }
        
        printf("Done!\n");                          
    } 
}

string get_contact_name()
{
    string name;
    do
    {
        name = get_string("Enter contact name: ");
    }
    while (contains(name, invalid));
    return name;
}

string get_contact_number()
{
    string number;
    do
    {
        number = get_string("Enter phone number: ");
    }
    while (!validate_number(number));
    return number;
}