#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

enum irq_type {
    IRQ_TYPE_LEVEL,
    IRQ_TYPE_EDGE,
    IRQ_TYPE_POLLING
};

static int irq_type = IRQ_TYPE_LEVEL; // default

#define TYPE_BUFF_MAX 16
static int irq_type_write(const char *val, const struct kernel_param *kp)
{
    char type[TYPE_BUFF_MAX];
    char *s;
    
    strncpy(type, val, TYPE_BUFF_MAX);
    type[TYPE_BUFF_MAX-1] = '\0';
    s = strstrip(type);
    
    if (strcmp(s, "level") == 0) {
        irq_type = IRQ_TYPE_LEVEL;
    }
    else if (strcmp(s, "edge") == 0) {
        irq_type = IRQ_TYPE_EDGE;
    }
    else if (strcmp(s, "polling") == 0) {
        irq_type = IRQ_TYPE_POLLING;
    }
    else {
        return -EINVAL;
    }
    return 0;
}

static int irq_type_read(char * buffer, const struct kernel_param *kp)
{
    switch (irq_type) {
    case IRQ_TYPE_LEVEL:
        strcpy(buffer, "Level");
        break;

    case IRQ_TYPE_EDGE:
        strcpy(buffer, "Edge");
        break;

    case IRQ_TYPE_POLLING:
        strcpy(buffer, "Polling");
        break;

    default:
        strcpy(buffer, "error");
        break;
    }

    return strlen(buffer);
}

static const struct kernel_param_ops irqtype_ops = {
    .set = irq_type_write,
    .get = irq_type_read
};

module_param_cb(irqtype, &irqtype_ops, NULL, 0660);
