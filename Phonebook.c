#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

string get_contact_data(int data_type);
int get_data_type(string data);
bool is_data_valid(string data, int data_type);
bool is_name_valid(string name);
bool is_phone_valid(string phone);

void start_add_contact(string data, int data_type);
void add_contact(string name, string phone);
void edit_contact(int position);
void print_contact_info(int position);
int find_contact_index(string data, int data_type);

string string_tolower(string z);

string data_types[] = {"name", "phone"};
int number_of_data_types = sizeof(data_types) / sizeof(data_types[0]);
char invalid[] = "+*/=0123456789";
int phonebook_size = 100;
string phonebook[100][2];

int count = 0;

int main(void)
{
    printf("\nWelcome to Phonebook!\n");
    while (true)
    {
        string data;
        int data_type;
        bool is_valid;
        do
        {
            data = get_string("\nEnter contact data: ");
            data_type = get_data_type(data);
            is_valid = is_data_valid(data, data_type);
            if (!is_valid)
            {
                printf("\nInvalid %s!\n", data_types[data_type]);
            }

        } while (!is_valid);

        int contact_index = find_contact_index(data, data_type);
        if (contact_index > -1)
        {
            printf("\nContact found:\n");
            print_contact_info(contact_index);
            edit_contact(contact_index);
            continue;
        }
        else
        {
            printf("\n%s not found. Creating new contact.\n", data);
            start_add_contact(data, data_type);
        }
    }
}

string get_contact_data(int data_type)
{
    string data;
    bool is_valid;
    do
    {
        data = get_string("\nEnter %s: ", data_types[data_type]);
        is_valid = is_data_valid(data, data_type);
        if (!is_valid)
        {
            printf("\nInvalid %s!\n", data_types[data_type]);
        }
    } while (!is_valid);

    return data;
}

int get_data_type(string data)
{
    // Houston, we have a problem...
    return is_phone_valid(data) ? 1 : 0;
}

bool is_data_valid(string data, int data_type)
{
    switch (data_type)
    {
    case 0:
        return is_name_valid(data);
    default:
        return is_phone_valid(data);
    }
}

bool is_name_valid(string name)
{
    if (name == NULL || name == "")
    {
        return false;
    }

    for (int i = 0; i < strlen(name); i++)
    {
        if (name[i] < 65 || name[i] > 90 && name[i] < 97 || name[i] > 122)
        {
            return false;
        }
    }

    return true;
}

bool is_phone_valid(string phone)
{
    if (phone == NULL || phone == "" || strlen(phone) <= 10 || strlen(phone) >= 15 || phone[0] != '+')
    {
        return false;
    }

    for (int i = 1, j = strlen(phone); i < j; i++)
    {
        if (phone[i] < 48 || phone[i] > 57)
        {
            return false;
        }
    }

    return true;
}

void start_add_contact(string data, int data_type)
{
    string contact[number_of_data_types];
    contact[data_type] = data;
    add_contact(contact[0], contact[1]);
}

void add_contact(string name, string phone)
{
    string data[] = {name, phone};
    for (int i = 0; i < number_of_data_types; i++)
    {
        if (!is_data_valid(data[i], i))
        {
            data[i] = get_contact_data(i);
        }

        phonebook[count][i] = data[i];
    }

    count++;
    printf("\nNew contact created.\n");
}

void edit_contact(int position)
{
    while (true)
    {
        int answer = 0;
        bool is_valid;
        do
        {
            printf("\nDo you want to edit something?\n");
            for (int i = 0; i < number_of_data_types; i++)
            {
                printf("  %i = edit %s\n", i + 1, data_types[i]);
            }

            printf("  0 = nothing\n");

            answer = get_int("\nPlease enter a number: ");
            is_valid = answer >= 0 && answer <= number_of_data_types;
            if (!is_valid)
            {
                printf("\nInvalid answer!\n");
            }
        } while (!is_valid);

        if (answer > 0)
        {
            int data_type = answer - 1;
            phonebook[position][data_type] = get_contact_data(data_type);
            printf("\nDone!\n");
        }
        else
        {
            printf("\nEditing finished!\n");
            return;
        }
    }
}

void print_contact_info(int position)
{
    if (position < 0 || position >= phonebook_size)
    {
        return;
    }

    for (int i = 0; i < number_of_data_types; i++)
    {
        printf("  %s\n", phonebook[position][i]);
    }

    printf("  #%i in the phonebook\n", position);
}

int find_contact_index(string data, int data_type)
{
    for (int i = 0; i < phonebook_size; i++)
    {
        string contact_data = phonebook[i][data_type];
        if (contact_data == NULL)
            return -1;

        if (strcmp(string_tolower(contact_data), string_tolower(data)) == 0)
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