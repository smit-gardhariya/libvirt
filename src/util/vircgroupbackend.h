/*
 * vircgroupbackend.h: methods for cgroups backend
 *
 * Copyright (C) 2018 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef __VIR_CGROUP_BACKEND_H__
# define __VIR_CGROUP_BACKEND_H__

# include "internal.h"

# include "vircgroup.h"

# define CGROUP_MAX_VAL 512

typedef enum {
    VIR_CGROUP_BACKEND_TYPE_V1 = 0,
    VIR_CGROUP_BACKEND_TYPE_LAST,
} virCgroupBackendType;

typedef bool
(*virCgroupAvailableCB)(void);

typedef bool
(*virCgroupValidateMachineGroupCB)(virCgroupPtr group,
                                   const char *name,
                                   const char *drivername,
                                   const char *machinename);

typedef int
(*virCgroupCopyMountsCB)(virCgroupPtr group,
                         virCgroupPtr parent);

typedef int
(*virCgroupDetectMountsCB)(virCgroupPtr group,
                           const char *mntType,
                           const char *mntOpts,
                           const char *mntDir);

typedef int
(*virCgroupDetectPlacementCB)(virCgroupPtr group,
                              const char *path,
                              const char *controllers,
                              const char *selfpath);

struct _virCgroupBackend {
    virCgroupBackendType type;

    /* Mandatory callbacks that need to be implemented for every backend. */
    virCgroupAvailableCB available;
    virCgroupValidateMachineGroupCB validateMachineGroup;
    virCgroupCopyMountsCB copyMounts;
    virCgroupDetectMountsCB detectMounts;
    virCgroupDetectPlacementCB detectPlacement;
};
typedef struct _virCgroupBackend virCgroupBackend;
typedef virCgroupBackend *virCgroupBackendPtr;

void
virCgroupBackendRegister(virCgroupBackendPtr backend);

virCgroupBackendPtr *
virCgroupBackendGetAll(void);

#endif /* __VIR_CGROUP_BACKEND_H__ */
