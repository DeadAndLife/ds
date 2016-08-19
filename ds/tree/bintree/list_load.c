#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct node_st {
      char data;
      struct node_st *left, *right;
} node_t;

static node_t *find_max(node_t *root)
{
      if (root->right == NULL) {
	    return root;
      }

      return find_max(root->right);
}

static node_t *find_min(node_t *root)
{
      if (root->left == NULL) {
	    return root;
      }

      return find_min(root->left);
}

static int insert(node_t **root, int data)
{
      node_t *newnode;

      if (*root == NULL) {
	    newnode = malloc(sizeof(node_t));
	    newnode->data = data;
	    newnode->left = NULL;
	    newnode->right = NULL;

	    *root = newnode;
	    return 0;
      }
      if (data <= (*root)->data) {
	    return insert(&(*root)->left, data);
      } else {
	    return insert(&(*root)->right, data);
      }
}

static void delete(node_t **root, int data)
{
      node_t *pos, *left, *right;

      if (*root == NULL) {
	    return;
      }

      if ((*root)->data == data) {
	    pos = *root;
	    left = pos->left;
	    right = pos->right;
	    if (left != NULL) {
		  *root = left;
		  find_max(left)->right = right;
	    } else {
		  *root = right;
	    }
	    free(pos);
	    return;
      } else if (data < (*root)->data) {
	    delete(&(*root)->left, data);
	    return;
      } else {
	    delete(&(*root)->right, data);
            return;
      }

}

static node_t *find(node_t *root, int data)
{
      if (root == NULL) {
	    return NULL;
      }

      if (root->data == data) {
	    return root;
      } else if (data < root->data) {
	    return find(root->left, data);
      } else {
	    return find(root->right, data);
      }
}

static node_t *__load(FILE *fp)
{
      char c;
      node_t *root;

      fread(&c, 1, 1, fp);
      printf("in __load(), read %c\n", c);
      if (c != '(') {
	    fprintf(stderr, "in __load(), file error.\n");
	    return NULL;
      }

      fread(&c, 1, 1, fp);
      printf("in __load(), read %c\n", c);
      if (c == ')') {
            return NULL;
      }

      root = malloc(sizeof(node_t));
      if (0) {

      }
      root->data = c;
      root->left = __load(fp);
      root->right = __load(fp);
      fread(&c, 1, 1, fp);
      printf("in __load(), read %c\n", c);

      return root;
}

static node_t *load(const char *path)
{
      FILE *fp;
      node_t *root;

      fp = fopen(path, "r");
      if (0) {

      }

      root = __load(fp);

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
      printf("%c\n\n", root->data);
      indent++;
      draw(root->left);
      indent--;
}

static int node_num(node_t *root)
{
      if (root == NULL) {
	    return 0;
      }

      return node_num(root->left) + 1 + node_num(root->right);
}

static void turn_left(node_t **root)
{
      node_t *tmp = *root;

      *root = tmp->right;
      find_min(*root)->left = tmp;
      tmp->right = NULL;
}

static void turn_right(node_t **root)
{
      node_t *tmp = *root;

      *root = tmp->left;
      find_max(*root)->right = tmp;
      tmp->left = NULL;
}

static void balance(node_t **root)
{
      int sub;

      if (*root == NULL) {
	    return;
      }

      sub = node_num((*root)->left) - node_num((*root)->right);
      while (sub > 1 || sub < -1) {
	    if (sub > 1) {
		  turn_right(root);
	    } else {
		  turn_left(root);
	    }
	    sub = node_num((*root)->left) - node_num((*root)->right);
      }
      balance(&(*root)->left);
      balance(&(*root)->right);

}

int main(void)
{
      node_t *root = NULL;

      //save("tmp", root);
      root = load("tmp");
      draw(root);

      return 0;
}
