from elftools.elf.elffile import ELFFile, Section
import sys


def encrypt_section(section: Section):
    print(section.data_size)
    print(section.header)


KEY = 3


def main():
    filename = sys.argv[1]

    section_addr = 0
    section_size = 0
    with ELFFile(open(filename, 'rb')) as elffile:
        print(elffile.header)
        for section_idx in range(elffile.num_sections()):
            section = elffile.get_section(section_idx)
            if section.name == "secret.b":
                section_addr = section.header["sh_addr"]
                section_size = section.header["sh_size"] - 1
                break
        if section_addr == 0:
            raise ValueError("didn't find secret.b")

    print(f"section start_address {hex(section_addr)}")
    print(f"section size {hex(section_size)}")

    with open(filename, 'rb') as src_elffile:
        with open(f"{filename}.elf", 'wb') as dst_elffile:
            dst_elffile.write(src_elffile.read(section_addr - 1))

            for i in range(section_size):
                print(f"address: {hex(src_elffile.tell())}")
                original_byte = int.from_bytes(src_elffile.read(1), sys.byteorder)
                print(f"og: {hex(original_byte)}")
                patched_byte = bytes([original_byte ^ 3])
                print(f"new: {hex(original_byte ^ 3)}")
                dst_elffile.write(patched_byte)

            dst_elffile.write(src_elffile.read())


if __name__ == '__main__':
    main()
