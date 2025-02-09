#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* Esta função é chamada quando o módulo é carregado */
int simple_init(void) {
    printk(KERN_INFO "Loading Module\n");
    return 0;
}

/* Esta função é chamada quando o módulo é removido */
void simple_exit(void) {
    printk(KERN_INFO "Removing Module\n");
}

/* Macros para registrar os pontos de entrada e saída do módulo */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Seu Nome");
