#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>

#include "metaphone_ptbr.h"

#define MAX_METAPHONE_LENGTH 4
#define DOUBLED_CHAR(i) ((*i) == (*(i - 1)))
#define WORD_EDGE(c) (c == L'\0' || isspace(c))

typedef struct {
  char *str;
  int bufsize;
} Metastring;

Metastring *metastring_create(char *init_str) {
  Metastring *s = (Metastring *)malloc(sizeof(Metastring));
  bzero(s, 1 * sizeof(Metastring));
  if (init_str == NULL)
    return s;

  s->bufsize = (strlen(init_str) + 1) * sizeof(char);
  s->str = (char *)malloc(s->bufsize);

  bzero(s->str, s->bufsize * sizeof(char));
  memcpy(s->str, init_str, s->bufsize);

  return s;
}

void metastring_destroy(Metastring *s, short preserve_string) {
  if (s == NULL) {
    return;
  }

  if ((s->str != NULL) && !preserve_string) {
    free(s->str);
    s->str = NULL;
  }

  free(s);
  s = NULL;
}

void metastring_buffer_increase(Metastring *s, int chars_needed) {
  if (s->str == NULL) {
    s->str = (char *)malloc(((s->bufsize + chars_needed) * sizeof(char)));
    s->bufsize = chars_needed * sizeof(char) + 1;
    bzero(s->str, s->bufsize);
  } else {
    size_t sizeCharsNeeded = (chars_needed * sizeof(char));
    s->str = (char *)realloc(s->str, (s->bufsize + sizeCharsNeeded));
    bzero((s->str + s->bufsize), sizeCharsNeeded);
    s->bufsize += sizeCharsNeeded;
  }
}

wchar_t to_upper(const wchar_t d) {
  wchar_t c;

  c = (wchar_t)towupper((wint_t)d);

  switch (c) {

  case L'Á':
  case L'À':
  case L'Ã':
  case L'Â':
  case L'Ä':
    return L'A';

  case L'É':
  case L'È':
  case L'Ẽ':
  case L'Ê':
  case L'Ë':
    return L'E';

  case L'Y':

  case L'Í':
  case L'Ì':
  case L'Ĩ':
  case L'Î':
  case L'Ï':
    return L'I';

  case L'Ó':
  case L'Ò':
  case L'Õ':
  case L'Ô':
  case L'Ö':
    return L'O';

  case L'Ú':
  case L'Ù':
  case L'Ũ':
  case L'Û':
  case L'Ü':
    return L'U';
  }

  return c;
}

wchar_t *make_upper_clean(wchar_t *i) {
  wchar_t *s = (wchar_t *)NULL, *aux = (wchar_t *)NULL;

  if (!i || *i == L'\0')
    return NULL;

  /* transforma todos em maiúsculas, com algumas simplificações */
  aux = i;
  while (*aux) {
    *aux = to_upper(*aux);
    aux++;
  }

  /* copia para o novo buffer, eliminando os duplicados. */
  s = (wchar_t *)malloc((wcslen(i) + 1) * sizeof(wchar_t));
  bzero(s, wcslen(i) + 1 * sizeof(char));

  aux = s;
  *aux = *i;
  aux++;
  i++;

  for (; *i; i++) {

    /* clean doubled chars. Not needed in portuguese, except 'R' and 'S' */
    if (DOUBLED_CHAR(i)) {
      if (*i != L'R' && *i != L'S')
        continue;

      /* caso mais de 2 caracteres seguidos, vá até o último. */
      while (*i && *i == *(i + 1))
        i++;
    }
    *aux = *i;
    aux++;
  }

  *aux = L'\0';
  return s;
}

wchar_t get_at(wchar_t *s, int pos) {
  if ((pos >= wcslen(s)))
    return '\0';
  return ((wchar_t) * (s + pos));
}

wchar_t get_simplified_at(wchar_t *s, int pos) {
  if ((pos >= wcslen(s)))
    return '\0';
  return ((wchar_t) * (s + pos));
}

size_t metastring_buffer_length(Metastring *metastring) {
  if (!metastring->bufsize)
    return 0;
  return (metastring->bufsize / sizeof(char)) - 1;
}

void metastring_add_char(Metastring *s, char new_str) {
  if (new_str == '\0')
    return;

  size_t bufferLength = metastring_buffer_length(s);
  metastring_buffer_increase(s, 1);
  s->str[bufferLength] = new_str;
}

void metastring_add(Metastring *s, char *new_str) {
  size_t add_length = strlen(new_str);
  size_t ptr = 0;
  for (; ptr < add_length; ptr++) {
    metastring_add_char(s, new_str[ptr]);
  }
}

int is_vowel(char chr) {
  switch (chr) {
  case 'A':
  case 'E':
  case 'I':
  case 'O':
  case 'U':
    return 1;
  }
  return 0;
}

char *metaphone_ptbr(const wchar_t *str, const int max_length) {
  size_t length = 0;

  wchar_t *original = NULL;
  wchar_t *tmp = NULL;
  Metastring *metastring = NULL;

  size_t current = 0;
  char *metacode = NULL;

  wchar_t current_char = L'\0';
  wchar_t last_char = L'\0';
  wchar_t ahead_char = L'\0';

  if (str == NULL)
    return NULL;

  tmp = wcsdup(str);
  original = make_upper_clean(tmp);
  free(tmp);
  tmp = NULL;

  if (!original)
    return NULL;

  metastring = metastring_create(NULL);
  length = wcslen(original);

  while (current < length) {
    current_char = get_simplified_at(original, current);
    switch (current_char) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
      if (WORD_EDGE(last_char))
        metastring_add_char(metastring, current_char);
      break;

    case 'L':
      ahead_char = get_at(original, current + 1);
      if (ahead_char == 'H')
        metastring_add_char(metastring, '1');
      else if (is_vowel(ahead_char) || WORD_EDGE(last_char))
        metastring_add_char(metastring, 'L');
      break;
    case 'T':
    case 'P':
      ahead_char = get_at(original, current + 1);
      if (ahead_char == 'H') {
        if (current_char == 'P')
          metastring_add_char(metastring, 'F');
        else
          metastring_add_char(metastring, 'T');
        current++;
        break;
      }
    /* FALLTHRU */
    case 'B':
    case 'D':
    case 'F':
    case 'J':
    case 'K':
    case 'M':
    case 'V':
      metastring_add_char(metastring, current_char);
      break;
    case 'G':
      ahead_char = get_simplified_at(original, current + 1);
      switch (ahead_char) {
      case 'H':
        if (!is_vowel(get_simplified_at(original, current + 2))) {
          metastring_add_char(metastring, 'G');
        }
      /* FALLTHRU */
      case 'E':
      case 'I':
        metastring_add_char(metastring, 'J');
        break;
      default:
        metastring_add_char(metastring, 'G');
        break;
      }
      break;
    case 'R':
      ahead_char = get_simplified_at(original, current + 1);
      if (WORD_EDGE(last_char) || WORD_EDGE(ahead_char)) {
        metastring_add_char(metastring, '2');
      } else if (ahead_char == 'R') {
        metastring_add_char(metastring, '2');
        current++;
      } else if (is_vowel(last_char) && is_vowel(ahead_char)) {
        metastring_add_char(metastring, 'R');
        current++;
      } else
        metastring_add_char(metastring, 'R');
      break;
    case 'Z':
      ahead_char = get_at(original, current + 1);
      if (WORD_EDGE(ahead_char))
        metastring_add_char(metastring, 'S');
      else
        metastring_add_char(metastring, 'Z');
      break;
    case 'N':
      ahead_char = get_at(original, current + 1);
      if (WORD_EDGE(ahead_char)) {
        metastring_add_char(metastring, 'M');
      } else if (ahead_char == 'H') {
        metastring_add_char(metastring, '3');
        current++;
      } else if (last_char != 'N') {
        metastring_add_char(metastring, 'N');
      }
      break;
    case 'S':
      ahead_char = get_simplified_at(original, current + 1);
      if (ahead_char == 'S') {
        metastring_add_char(metastring, 'S');
        last_char = ahead_char;
        current++;
      } else if (ahead_char == 'H') {
        metastring_add_char(metastring, 'X');
        current++;
      } else if (is_vowel(last_char) && is_vowel(ahead_char)) {
        metastring_add_char(metastring, 'Z');
      } else if (ahead_char == 'C') {
        wchar_t ahead2_char = get_simplified_at(original, current + 2);
        switch (ahead2_char) {
        case L'E':
        case L'I':
          metastring_add_char(metastring, 'S');
          current += 2;
          break;
        case L'A':
        case L'O':
        case L'U':
          metastring_add(metastring, "SK");
          current += 2;
          break;
        case L'H':
          metastring_add_char(metastring, 'X');
          current += 2;
          break;
        default:
          metastring_add_char(metastring, 'S');
          current++;
          break;
        }
      } else
        metastring_add_char(metastring, 'S');
      break;
    case 'X': {
      wchar_t last2_char = get_at(original, current - 2);
      ahead_char = get_simplified_at(original, current + 1);
      if (WORD_EDGE(ahead_char)) {
        metastring_add_char(metastring, 'X');
      } else if (last_char == 'E') {
        if (is_vowel(ahead_char)) {
          if (WORD_EDGE(last2_char)) {
            metastring_add_char(metastring, 'Z');
          } else
            switch (ahead_char) {
            case 'E':
            case 'I':
              metastring_add_char(metastring, 'X');
              current++;
              break;
            default:
              metastring_add(metastring, "KS");
              current++;
              break;
            }
        } else if (ahead_char == 'C') {
          metastring_add_char(metastring, 'S');
          current++;
        } else if (ahead_char == 'P' || ahead_char == 'T')
          metastring_add_char(metastring, 'S');
        else
          metastring_add(metastring, "KS");
      } else if (is_vowel(last_char)) {
        switch (last2_char) {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
        case 'C':
        case 'K':
        case 'G':
        case 'L':
        case 'R':
        case 'X':
          metastring_add_char(metastring, 'X');
          break;
        default:
          metastring_add(metastring, "KS");
          break;
        }
      } else
        metastring_add_char(metastring, 'X');
    } break;
    case 'C':
      ahead_char = get_simplified_at(original, current + 1);
      switch (ahead_char) {
      case 'E':
      case 'I':
        metastring_add_char(metastring, 'S');
        break;
      case 'H':
        if (get_simplified_at(original, current + 2) == 'R')
          metastring_add_char(metastring, 'K');
        else
          metastring_add_char(metastring, 'X');
        current++;
        break;
      case 'Q':
      case 'K':
        break;
      default:
        metastring_add_char(metastring, 'K');
        break;
      }
      break;
    case 'H':
      if (WORD_EDGE(last_char)) {
        ahead_char = get_simplified_at(original, current + 1);
        if (is_vowel(ahead_char)) {
          metastring_add_char(metastring, ahead_char);
          current++;
        }
      }
      break;
    case 'Q':
      metastring_add_char(metastring, 'K');
      break;
    case 'W':
      ahead_char = get_simplified_at(original, current + 1);
      if (is_vowel(ahead_char))
        metastring_add_char(metastring, 'V');
      break;
    case L'Ç':
      metastring_add_char(metastring, 'S');
      break;
    }
    current++;
    last_char = current_char;
  }

  free(original);

  metacode = metastring->str;
  metastring_destroy(metastring, 1);
  return metacode;
}
