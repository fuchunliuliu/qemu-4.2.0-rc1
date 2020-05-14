/*
 * Internal definitions for a target's KVM support
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#ifndef QEMU_KVM_INT_H
#define QEMU_KVM_INT_H

#include "exec/memory.h"
#include "sysemu/accel.h"
#include "sysemu/kvm.h"

typedef struct KVMSlot
{
	/* 客户机物理地址 */
    hwaddr start_addr;
	/* 内存大小 */
    ram_addr_t memory_size;
	/* hva, qemu用户空间地址 */
    void *ram;
	/* slot编号 */
    int slot;
    int flags;
    int old_flags;
    /* Dirty bitmap cache for the slot */
    unsigned long *dirty_bmap;
} KVMSlot;

typedef struct KVMMemoryListener {
    MemoryListener listener;
    /* Protects the slots and all inside them */
    QemuMutex slots_lock;
    KVMSlot *slots;
    int as_id;
} KVMMemoryListener;

#define TYPE_KVM_ACCEL ACCEL_CLASS_NAME("kvm")

#define KVM_STATE(obj) \
    OBJECT_CHECK(KVMState, (obj), TYPE_KVM_ACCEL)

void kvm_memory_listener_register(KVMState *s, KVMMemoryListener *kml,
                                  AddressSpace *as, int as_id);

void kvm_set_max_memslot_size(hwaddr max_slot_size);
#endif
