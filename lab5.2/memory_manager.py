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
