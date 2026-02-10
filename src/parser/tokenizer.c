#include "parser.h"

/* Simplified file reader buffer size */
#define BUFFER_SIZE 4096

/* External helpers from core/utils.c */
int     ft_strlen(const char *s);
char    *ft_strdup(const char *s);
int     is_space(char c);

static t_token *new_token(char *content)
{
    t_token *t;
    
    t = malloc(sizeof(t_token));
    if (!t)
        return (NULL);
    t->content = content;
    t->next = NULL;
    return (t);
}

static void token_add_back(t_token **head, t_token *new_t)
{
    t_token *tmp;

    if (!*head)
    {
        *head = new_t;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_t;
}

/* extract next word from start until whitespace */
static char *extract_word(char *str, int *i)
{
    int start;
    int len;
    char *word;
    int j;

    start = *i;
    while (str[*i] && !is_space(str[*i]))
        (*i)++;
    len = *i - start;
    word = malloc(len + 1);
    j = 0;
    while (j < len)
    {
        word[j] = str[start + j];
        j++;
    }
    word[j] = '\0';
    return (word);
}

/* Reads file and returns full content string */
static char *read_full_file(const char *filename)
{
    int     fd;
    char    buffer[BUFFER_SIZE];
    char    *full_content;
    char    *temp;
    int     bytes_read;
    int     total_len;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    full_content = ft_strdup(""); // Start empty
    total_len = 0;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        temp = malloc(total_len + bytes_read + 1);
        int i = 0;
        int k = 0;
        while (full_content[i]) 
            temp[k++] = full_content[i++];
        i = 0;
        while (buffer[i])
            temp[k++] = buffer[i++];
        temp[k] = '\0';
        free(full_content);
        full_content = temp;
        total_len += bytes_read;
    }
    close(fd);
    return (full_content);
}

t_token *tokenize_file(const char *filename)
{
    char    *content;
    t_token *head;
    int     i;

    content = read_full_file(filename);
    if (!content)
        return (NULL);
    
    head = NULL;
    i = 0;
    while (content[i])
    {
        while (content[i] && is_space(content[i]))
            i++;
        if (!content[i])
            break;
        token_add_back(&head, new_token(extract_word(content, &i)));
    }
    free(content);
    return (head);
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->content);
        free(tmp);
    }
}
