#include "json.h"

void print_json(JSON* j) {
   int i;
   switch (j->type) {
   case json_str:
      printf("%s", (char*)(j->p));
      break;
   case json_num:
      printf("%Le", *((long double*)(j->p)));
      break;
   case json_dict: {
      JSON_DICT *d = (JSON_DICT*)(j->p);
      for (i = 0; i < d->num_entries; i++) {
         printf("key: %s", d->keys[i]);
         printf("value: ");
         print_json(d->entries[i]);
      }
      break;
   }
   case json_lst: {
      JSON_LST *l = (JSON_LST*)(j->p);
      for (i = 0; i < l->items_len; i++) {
         print_json(&(l->items[i]));
      }
      break;
   }
   default:
      printf("bad json type");
      break;
   }
}

char* lex_to_str(LEXEME* l) {
   char str_num[100];
   memset(str_num, 0, sizeof str_num);

   switch (l->type) {
   case l_open_dict:
      return "{";
   break;
   case l_close_dict:
      return "}";
   break;
   case l_open_lst:
      return "[";
   break;
   case l_close_lst:
      return "]";
   break;
   case l_semi:
      return ":";
   break;
   case l_comma:
      return ",";
   break;
   case l_str:
      return l->str_value;
   break;
   case l_num:
      sprintf(str_num, "%Lg", l->num_value);
      return str_num;
   break;
   default:
      return "Bad lexeme type";
   break;
   }
}

void print_space(int n) {
   int i;
   for (i = 0; i < n; i++)
      putchar(' ');
}

void printLexTree(LexTree* tree, int level) {
   //printf("=============\n");
   int i;

   for (i = 0; i < tree->num; i++) {
      if (tree->elems[i].atom) {
         print_space(level);
         printf("%s\n", lex_to_str(tree->elems[i].l));
      }
      else {
         printLexTree(tree->elems[i].t, level + 4);
      }
   }
   //printf("=============\n");
}

