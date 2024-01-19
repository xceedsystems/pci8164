//#include "acl_pci.h"
#define SUCCESSFUL			0x00
#define NOT_SUCCESSFUL		0x01


#define PCI_CS_VENDOR_ID	 0x00
#define PCI_CS_DEVICE_ID	 0x02
#define PCI_CS_COMMAND		 0x04
#define PCI_CS_STATUS		 0x06
#define PCI_CS_REVISION_ID	 0x08
#define PCI_CS_CLASS_CODE	 0x09
#define PCI_CS_CACHE_LINE_SIZE	 0x0C
#define PCI_CS_MASTER_LATENCY	 0x0D
#define PCI_CS_HEADER_TYPE	 0x0E
#define PCI_CS_BIST		 0x0F
#define PCI_CS_BASE_ADDRESS_0	 0x10
#define PCI_CS_BASE_ADDRESS_1	 0x14
#define PCI_CS_BASE_ADDRESS_2	 0x18
#define PCI_CS_BASE_ADDRESS_3	 0x1C
#define PCI_CS_BASE_ADDRESS_4	 0x20
#define PCI_CS_BASE_ADDRESS_5	 0x24
#define PCI_CS_Subsystem_VID	 0x2C
#define PCI_CS_Subsystem_ID	 0x2E
#define PCI_CS_EXPANSION_ROM	 0x30
#define PCI_CS_INTERRUPT_LINE	 0x3C
#define PCI_CS_INTERRUPT_PIN	 0x3D
#define PCI_CS_MIN_GNT		 0x3E
#define PCI_CS_MAX_LAT		 0x3F

typedef unsigned char	byte;	/* 8-bit  */
typedef unsigned short	word;	/* 16-bit */
typedef unsigned long	dword;	/* 32-bit */

int pci_bios_present(byte *hardware_mechanism,
			    word *interface_level_version,
			    byte *last_pci_bus_number);

int find_pci_device(word device_id,
		    word vendor_id,
		    word index,
		    byte *bus_number,
		    byte *device_and_function);

int read_configuration_area(byte function,
				   byte bus_number,
				   byte device_and_function,
				   byte register_number,
				   dword *data);

int write_configuration_area(byte function,
				    byte bus_number,
				    byte device_and_function,
				    byte register_number,
				    dword value);
