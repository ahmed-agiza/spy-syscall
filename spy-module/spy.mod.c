#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
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
	{ 0xc9091f09, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x4470a79b, __VMLINUX_SYMBOL_STR(param_ops_long) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xbdf3a5a, __VMLINUX_SYMBOL_STR(sock_from_file) },
	{ 0xc21240c2, __VMLINUX_SYMBOL_STR(d_path) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2053de69, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x94da47a9, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9790a88, __VMLINUX_SYMBOL_STR(init_task) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "825A1FA230A1EA66772FC34");
