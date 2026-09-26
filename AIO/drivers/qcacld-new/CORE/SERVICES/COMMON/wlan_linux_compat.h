/*
 * Copyright (c) 2026 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * wlan_linux_compat.h - small shims for kernel APIs that were renamed or
 * removed after 5.15, so the same sources build on both 5.15 and 6.12
 * (Android GKI) kernels.  Every shim is keyed on LINUX_VERSION_CODE and
 * maps the old name onto the in-kernel replacement, so nothing changes
 * when building for older kernels.
 */
#ifndef _WLAN_LINUX_COMPAT_H_
#define _WLAN_LINUX_COMPAT_H_

#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/netdevice.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>

/* 5.17: PDE_DATA() renamed to pde_data() */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 17, 0)
#ifndef PDE_DATA
#define PDE_DATA(inode) pde_data(inode)
#endif
#endif

/* 5.17: complete_and_exit() renamed to kthread_complete_and_exit() */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 17, 0)
#ifndef complete_and_exit
#define complete_and_exit(comp, code) kthread_complete_and_exit(comp, code)
#endif
#endif

/* 5.18: netif_rx() may be called from any context; netif_rx_ni() removed */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 18, 0)
#ifndef netif_rx_ni
#define netif_rx_ni(skb) netif_rx(skb)
#endif
#endif

/* 6.12: no_llseek removed; a NULL llseek now means "not seekable" */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0)
#ifndef no_llseek
#define no_llseek NULL
#endif
#endif

#endif /* _WLAN_LINUX_COMPAT_H_ */
