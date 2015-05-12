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
	{ 0x274787d4, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xf20bc8cf, __VMLINUX_SYMBOL_STR(sock_from_file) },
	{ 0x648d246b, __VMLINUX_SYMBOL_STR(d_path) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x839466b, __VMLINUX_SYMBOL_STR(pid_task) },
	{ 0xc93c9688, __VMLINUX_SYMBOL_STR(find_vpid) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc671c06e, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x91816465, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "DF6F78525F8CD8CA59AEC42");
