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
      int arr[] = {5, 3, 8, 4, 1, 7, 6, 9};
      int i;
      node_t *root = NULL;
      node_t *new;

      for (i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
	    insert(&root, arr[i]);
      }

      draw(root);
      save("tmp", root);

      return 0;
}
