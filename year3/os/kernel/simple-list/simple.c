#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

/* Estrutura para armazenar aniversários */
struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

/* Cabeça da lista de aniversários */
static LIST_HEAD(birthday_list);

/* Esta função é chamada quando o módulo é carregado */
int simple_init(void) {
    struct birthday *person;
    int i;

    printk(KERN_INFO "Loading Module\n");

    /* Criar e adicionar 5 elementos à lista */
    for (i = 0; i < 5; i++) {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = i + 1;
        person->month = 12 - i;
        person->year = 1990 + i;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
        printk(KERN_INFO "Added: %d-%d-%d\n", person->day, person->month, person->year);
    }

    return 0;
}

/* Esta função é chamada quando o módulo é removido */
void simple_exit(void) {
    struct birthday *ptr, *next;

    printk(KERN_INFO "Removing Module\n");

    /* Remover e liberar os elementos da lista */
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        printk(KERN_INFO "Removing: %d-%d-%d\n", ptr->day, ptr->month, ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }
}

/* Macros para registrar os pontos de entrada e saída do módulo */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module with Linked List");
MODULE_AUTHOR("Seu Nome");
