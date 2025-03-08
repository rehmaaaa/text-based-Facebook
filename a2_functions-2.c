/*****************
    Student Name 	= Rehma Muzammil
    Student Number	= 101268686
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here
user_t *add_user(user_t *users, const char *username, const char *password)
{
    user_t *new_user = malloc(sizeof(user_t));
    assert(new_user != NULL);
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->friends = NULL;
    new_user->posts = NULL;
    if (users == NULL || strcmp(new_user->username, users->username) < 0)
    {
        new_user->next = users;
        return new_user;
    }
    user_t *temp = users;
    while (temp->next != NULL && strcmp(new_user->username, temp->next->username) > 0)
    {
        temp = temp->next;
    }
    new_user->next = temp->next;
    temp->next = new_user;
    return users;
}

/* finds user in the database */
user_t *find_user(user_t *users, const char *username)
{
    while (users != NULL)
    {
        if (strcmp(users->username, username) == 0)
        {
            return users;
        }
        users = users->next;
    }
    return NULL;
}
/* function that creates a new friend */
friend_t *create_friend(const char *username)
{
    if (!username)
    {
        printf("Invalid friend username.\n");
        return NULL;
    }

    friend_t *new_friend = malloc(sizeof(friend_t));
    if (!new_friend)
    {
        printf("Memory allocation failed for friend.\n");
        return NULL;
    }

    strncpy(new_friend->username, username, 29);
    new_friend->username[29] = '\0';
    new_friend->next = NULL;
    return new_friend;
}

void add_friend(user_t *user, const char *friends_name)
{

    friend_t *new_friend = create_friend(friends_name);

    // Insert in the beginning if list is empty or friend name comes first
    if (!user->friends || strcmp(friends_name, user->friends->username) < 0)
    {
        new_friend->next = user->friends;
        user->friends = new_friend;
        return;
    }
    friend_t *current = user->friends;
    while (current->next != NULL && strcmp(user->friends->username, new_friend->username) > 0)
    {
        current = current->next;
    }

    new_friend->next = current->next;
    current->next = new_friend;
}

post_t *create_post(const char *text)
{
    if (!text || strlen(text) == 0)
    {
        printf("Invalid post content.\n");
        return NULL;
    }

    post_t *new_post = (post_t *)malloc(sizeof(post_t));
    if (!new_post)
    {
        printf("Memory allocation failed for post.\n");
        return NULL;
    }

    strncpy(new_post->content, text, 249);
    new_post->content[249] = '\0';
    new_post->next = NULL;
    return new_post;
}

void add_post(user_t *user, const char *text)
{
    if (!user || !text) return;
    
    post_t *new_post = create_post(text);
    if (!new_post) return;
    
    new_post->next = user->posts;
    user->posts = new_post;
}

_Bool delete_post(user_t *user)
{
    if (!user || !user->posts)
    {
        printf("No posts to delete.\n");
        return false;
    }

    post_t *temp = user->posts;
    user->posts = user->posts->next;
    free(temp);
    printf("Post deleted successfully.\n");
    return true;
}

void display_all_user_posts(user_t *user)
{
    if (!user)
    {
        printf("Invalid user.\n");
        return;
    }

    post_t *current = user->posts;
    if (!current)
    {
        return;
    }

    printf("\n=== Posts by %s ===\n", user->username);
    int count = 1;
    while (current)
    {
        printf("%d. %s\n", count++, current->content);
        current = current->next;
    }
}

void display_user_friends(user_t *user)
{
    if (!user)
    {
        printf("Invalid user.\n");
        return;
    }

    friend_t *current = user->friends;
    if (!current)
    {
        printf("No friends to display.\n");
        return;
    }

    printf("\n=== Friends of %s ===\n", user->username);
    int count = 1;
    while (current)
    {
        printf("%d. %s\n", count++, current->username);
        current = current->next;
    }
}

_Bool delete_friend(user_t *user, char *friend_name)
{
    if (!user || !user->friends || !friend_name)
    {
        printf("Invalid input.\n");
        return false;
    }

    if (strcmp(user->friends->username, friend_name) == 0)
    {
        friend_t *temp = user->friends;
        user->friends = user->friends->next;
        free(temp);
        printf("Friend '%s' removed successfully.\n", friend_name);
        return true;
    }

    friend_t *current = user->friends;
    while (current->next)
    {
        if (strcmp(current->next->username, friend_name) == 0)
        {
            friend_t *temp = current->next;
            current->next = current->next->next;
            free(temp);
            printf("Friend '%s' removed successfully.\n", friend_name);
            return true;
        }
        current = current->next;
    }

    printf("Friend '%s' not found.\n", friend_name);
    return false;
}

void display_posts_by_n(user_t *user, int number)
{
    if (!user || number <= 0)
    {
        printf("Invalid user or number of posts to display.\n");
        return;
    }

    post_t *current = user->posts;
    int displayed = 0;
    char response = 'y';

    while (current && (response == 'y' || response == 'Y'))
    {
        for (int i = 0; i < number && current; i++)
        {
            printf("%d. %s\n", displayed + 1, current->content);
            current = current->next;
            displayed++;
        }

        if (current)
        {
            printf("\n Do you want to display more posts? (y/n): ");
            scanf(" %c", &response);
            getchar(); 
        }
    }

    if (!current)
        printf("\nAll posts have been displayed.\n");
}

void teardown(user_t *users)
{
    while (users) {
        while (users->posts) {
            post_t *temp_post = users->posts;
            users->posts = users->posts->next;
            free(temp_post);
        }
        while (users->friends) {
            friend_t *temp_friend = users->friends;
            users->friends = users->friends->next;
            free(temp_friend);
        }
        user_t *temp_user = users;
        users = users->next;
        free(temp_user);
    }
}


void print_menu()
{
    printf("***********************************\n");
    printf("             Main Menu             \n");
    printf("***********************************\n");
    printf("1. Register a new user \n2. Manage a user's profile\n3. Manage a user's posts\n4. Manage a user's friends\n5. Display all Posts\n6. Exit\n\n");
    printf("Enter your choice: ");
}
/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}