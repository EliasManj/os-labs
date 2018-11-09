from numpy import array, roll

#Function for TLB search
def TLB_search(page_number):
    for tlb_item in TLB:
        if tlb_item["page"] == page_number:
            return tlb_item["frame"]
    return None

#Push to TLB
def TLB_add(TLB, page_number, frame_number):
    TLB = roll(TLB, 1)
    TLB[0]["page"] = page_number
    TLB[0]["frame"] = frame_number
    return TLB

#Read 256 bytes from binary file
def backing_store_read(page_number):
    store_add = page_number*256
    with open("BACKING_STORE.bin", "rb") as f:
        f.seek(store_add)
        for i in range(256):
            data = f.read(1)
            physical_memory[frame*PAGE_SIZE+i] = data

#import all virtual addresses from text file
def read_virtual_addresses(filename):
    with open(filename) as f:
        virtual_addresses = f.readlines()
    return [int(x.strip()) for x in virtual_addresses]

def signed_ord(byte):
        unsigned = ord(byte)
        return unsigned - 256 if unsigned > 127 else unsigned

if __name__ == "__main__":
    filename = "addresses.txt"
    #Sizes 
    PAGE_SIZE = 256
    NUMBER_OF_PAGES = 256
    TLB_SIZE = 16
    #Masks
    page_number_mask = 65280
    offset_mask = 255
    #Data structures
    page_table = [None]*NUMBER_OF_PAGES
    physical_memory = [None]*NUMBER_OF_PAGES*PAGE_SIZE
    #Other
    frame = 0
    n_hits = 0
    #TLB
    TLB = []
    #Create table lookaside buffer of size 15
    for i in range(TLB_SIZE):
        TLB.append({"page":-1, "frame": -1})
    TLB = array(TLB)
    #Main program
    with open("test.txt", "w") as myfile:
        virtual_addresses = read_virtual_addresses(filename)
        for virtual_add in virtual_addresses:
            page_number = virtual_add&page_number_mask
            page_number = page_number>>8
            page_offset = virtual_add&255
            tlb_frame = TLB_search(page_number)
            if tlb_frame:
                #If hit
                physical_address = tlb_frame*256 + page_offset
                n_hits = n_hits + 1
            elif not page_table[page_number]:
                #If Page fault read from backing store
                backing_store_read(page_number)
                page_table[page_number] = frame
                TLB = TLB_add(TLB, page_number, frame)
                frame = frame + 1
                physical_address = page_table[page_number]*256 + page_offset
            else:
                TLB = TLB_add(TLB, page_number, page_table[page_number])
                physical_address = page_table[page_number]*256 + page_offset
            value = physical_memory[physical_address]
            myfile.write("Virtual address: {} Physical address: {} Value: {}\n".format(virtual_add, physical_address, signed_ord(value)))
