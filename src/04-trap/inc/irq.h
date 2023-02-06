#ifndef _IRQ_H_
#define _IRQ_H_

typedef void (*irq_handler_t)(void);

enum irq_id {
	IRQ_VIRTIO = 1,
	IRQ_VIRTIO_CNT = 8,
	IRQ_UART0 = 10,
	IRQ_RTC = 11,
	IRQ_PCIE = 32,
	__IRQ_MAX_ID,
};

extern void (*external_irq_handler)(void);
#endif /* _IRQ_H_ */
