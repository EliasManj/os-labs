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

def read_virtual_addresses(filename):
    with open(filename) as f:
        virtual_addresses = f.readlines()
    return [int(x.strip()) for x in virtual_addresses]

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