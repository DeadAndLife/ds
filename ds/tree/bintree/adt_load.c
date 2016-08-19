#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct node_st {
      int *data;
      struct node_st *left, *right;
} node_t;


static int insert(node_t **root, int data)
{
      node_t *newnode;

      if (*root == NULL) {
	    newnode = malloc(sizeof(node_t));
	    newnode->data = malloc(sizeof(int));
	    *newnode->data = data;
	    newnode->left = NULL;
	    newnode->right = NULL;

	    *root = newnode;
	    return 0;
      }
      if (data <= *(*root)->data) {
	    return insert(&(*root)->left, data);
      } else {
	    return insert(&(*root)->right, data);
      }
}

static void save_list(FILE *fp, node_t *root)
{
      if (root == NULL) {
	    fwrite("0", 1, 1, fp);
	    return;
      }

      fwrite("(", 1, 1, fp);
      fwrite("1", 1, 1, fp);
      save_list(fp, root->left);
      save_list(fp, root->right);
      fwrite(")", 1, 1, fp);
}

static void __save_data(FILE *fp, node_t *root)
{
      if (root == NULL) {
	    return;
      }

      fwrite(root->data, sizeof(int), 1, fp);
      __save_data(fp, root->left);
      __save_data(fp, root->right);
}

static void save_data(FILE *fp, node_t *root, long offset)
{
      if (root == NULL) {
	    fwrite("0", 1, 1, fp);
	    return;
      }

      fseek(fp, offset, SEEK_SET);

      __save_data(fp, root);
}

static void save(const char *path, node_t *root)
{
      FILE *fp;
      long offset = 1024;
      int size = sizeof(int);

      fp = fopen(path, "w");
      if (0) {

      }

      fwrite(&size, sizeof(size), 1, fp);
      fwrite(&offset, sizeof(offset), 1, fp);
      save_list(fp, root);
      save_data(fp, root, offset);

      fclose(fp);
}

static node_t *__load(FILE *fp, FILE *data_fp, int size)
{
      char c;
      node_t *root;
      fpos_t pos;

      fread(&c, sizeof(char), 1, fp);
      if (c == '0') {
	    return NULL;
      }
      if (c != '(') {
	    fgetpos(fp, &pos);
	    fprintf(stderr, "in __load(): format error. cur = %lld, getchar = %x\n", pos, c);
	    return NULL;
      }
      fread(&c, sizeof(char), 1, fp);
      if (c != '1') {

      }
      root = malloc(sizeof(node_t));
      root->data = malloc(size);
      fread(root->data, size, 1, data_fp);
      root->left = __load(fp, data_fp, size);
      root->right = __load(fp, data_fp, size);
      fread(&c, sizeof(char), 1, fp);

      return root;
}

static node_t *load(const char *path)
{
      FILE *fp, *data_fp;
      long offset;
      int size;
      node_t *root;
      fpos_t pos;

      fp = fopen(path, "r");
      if (0) {

      }
      data_fp = fopen(path, "r");
      if (0) {

      }

      fread(&size, sizeof(int), 1, fp);
      fgetpos(fp, &pos);
      printf("in load(): cur = %lld\n", pos);
      fread(&offset, sizeof(long), 1, fp);
      fgetpos(fp, &pos);
      printf("in load(): cur = %lld\n", pos);
      fseek(data_fp, offset, SEEK_SET);
      fgetpos(fp, &pos);
      printf("in load(): cur = %lld\n", pos);

      root = __load(fp, data_fp, size);

      fclose(data_fp);
      fclose(fp);

      return root;
}

static void draw(node_t *root)
{
      static int indent = 0;
      int i;

      if (root == NULL) {
	    return;
      }

      indent++;
      draw(root->right);
      indent--;
      for (i = 0; i < indent; i++) {
	    putchar('\t');
      }
      printf("%d\n\n", *root->data);
      indent++;
      draw(root->left);
      indent--;
}

int main(void)
{
      node_t *root = NULL;

      root = load("tmp");
      draw(root);

      return 0;
}
