#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x135dd1a3, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x7a8cea8a, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x68da632c, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xf743575b, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x90679b51, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x98aac78b, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x6556df31, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x9d70af65, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xd1ec4656, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x6e0c8b24, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0xc01cf848, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0x7f658e80, __VMLINUX_SYMBOL_STR(_raw_write_lock) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "2E5E9DABE1317D410AE3A98");
