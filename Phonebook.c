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
int find_contact_index(string data, string data_type);
int find_name_index(string name);
int find_number_index(string number);
void edit_contact(int i);
string get_contact_data();
string get_data_type(string data);
string get_contact_name();
string get_contact_number();

string phonebook[100][2];
char invalid[] = "+*/=0123456789";
string data_types_dictionary[] = {
    {"name","0"},
    {"number","1"}
};
int count = 0;

int main (void)
{
    printf("Welcome to Phonebook!\n");
    while (true)
    {
        string data = get_string("Enter contact data: ");
        string data_type = get_data_type(data);

        int contact_index = find_contact_index(data, data_type);
        if (contact_index > -1)
        {
            printf("Contact found:\n");
            print_contact_info(contact_index);
            edit_contact(contact_index);
            continue;
        }
        else
        {
            printf("%s not found. Creating new contact.\n", data);
        }

        string number;
        string name;
        if (data_type == "name") 
        {
            name = data;
            number = get_contact_number();
        }
        else
        {
            number = data;
            name = get_contact_name();
        }

        phonebook[count][0] = name;
        phonebook[count][1] = number;
        count++;
        printf("New contact created.\n");
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

int find_contact_index(string data, string data_type)
{
    if (data_type == "name") 
    {
        return find_name_index(data);
    }
    else
    {
        return find_number_index(data);
    }
}

int find_name_index(string name)
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

int find_number_index(string number)
{
    for (int i = 0, j = sizeof(phonebook); i < j; i++)
    {
        string contact_number = phonebook[i][1];
        if (contact_number == NULL)
            return -1;

        if (strcmp(contact_number, number) == 0)
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

string get_data_type(string data)
{
    return validate_number(data) ? "number" : "name";
}

string get_contact_name()
{
    string name;
    bool is_valid;
    do
    {
        name = get_string("Enter contact name: ");
        is_valid = contains(name, invalid);
        if (!is_valid)
        {
            printf("Invalid contact name.\n");
        }
    }
    while (!is_valid);
    return name;
}

string get_contact_number()
{
    string number;
    bool is_valid;
    do
    {
        number = get_string("Enter phone number: ");
        is_valid = validate_number(number);
        if (!is_valid)
        {
            printf("Invalid phone number.\n");
        }
    }
    while (!is_valid);
    return number;
}

