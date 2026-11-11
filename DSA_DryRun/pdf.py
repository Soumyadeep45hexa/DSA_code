import re, math
from reportlab.lib.pagesizes import A4
from reportlab.lib import colors
from reportlab.lib.units import mm
from reportlab.lib.styles import ParagraphStyle
from reportlab.lib.enums import TA_CENTER
from reportlab.platypus import (BaseDocTemplate, PageTemplate, Frame, Paragraph, Spacer,
                                PageBreak, Table, TableStyle, KeepTogether, NextPageTemplate)
from reportlab.graphics.shapes import Drawing, Rect, String, Line, Circle
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont


D = "C:\\Windows\\Fonts\\"

pdfmetrics.registerFont(TTFont("DV", D + "arial.ttf"))
pdfmetrics.registerFont(TTFont("DV-B", D + "arialbd.ttf"))
pdfmetrics.registerFont(TTFont("DV-I", D + "ariali.ttf"))
pdfmetrics.registerFont(TTFont("DV-BI", D + "arialbi.ttf"))

pdfmetrics.registerFontFamily(
    "DV",
    normal="DV",
    bold="DV-B",
    italic="DV-I",
    boldItalic="DV-BI"
)
PAGE_W, PAGE_H = A4
MARGIN = 18 * mm
W = PAGE_W - 2 * MARGIN

HX = colors.HexColor
INK = HX("#1f2937")
GREEN, AMBER, BLUE, PINK = HX("#BDE5C8"), HX("#FFE08A"), HX("#B9D8F7"), HX("#F7B8C4")
ORANGE, PURPLE, TEAL, GREY = HX("#FFC98B"), HX("#D9C6F2"), HX("#B5E6E0"), HX("#E5E7EB")

ACC = {
    "intro": HX("#374151"),
    "bubble": HX("#2563EB"),
    "insertion": HX("#059669"),
    "shell": HX("#D97706"),
    "merge": HX("#7C3AED"),
    "quick": HX("#DC2626"),
    "heap": HX("#0D9488"),
    "radix": HX("#DB2777"),
    "final": HX("#374151"),
}
LIGHT = {k: colors.Color(v.red * 0.12 + 0.88, v.green * 0.12 + 0.88, v.blue * 0.12 + 0.88) for k, v in ACC.items()}


def fx(s):
    return re.sub(r"\^([\d.]+)", r"<super>\1</super>", s)


body = ParagraphStyle("body", fontName="DV", fontSize=9.6, leading=14.2, spaceAfter=5, textColor=INK)
small = ParagraphStyle("small", parent=body, fontSize=8.4, leading=11.5, spaceAfter=2)
cap = ParagraphStyle("cap", parent=body, fontName="DV-I", fontSize=8.4, leading=11, textColor=HX("#4b5563"), spaceAfter=8)
cell = ParagraphStyle("cell", parent=body, fontSize=8.6, leading=11.5, spaceAfter=0)
cellb = ParagraphStyle("cellb", parent=cell, fontName="DV-B")
cellc = ParagraphStyle("cellc", parent=cell, alignment=TA_CENTER)
bul = ParagraphStyle("bul", parent=body, leftIndent=16, bulletIndent=4, spaceAfter=3)
codest = ParagraphStyle("code", fontName="DV", fontSize=8, leading=10.6, textColor=HX("#111827"))


def P(t, st=body):
    return Paragraph(fx(t), st)


def H2(t, key):
    st = ParagraphStyle("h2" + key, parent=body, fontName="DV-B", fontSize=13, leading=17,
                        spaceBefore=11, spaceAfter=5, textColor=ACC[key], keepWithNext=1)
    return Paragraph(fx(t), st)


def H3(t, key):
    st = ParagraphStyle("h3" + key, parent=body, fontName="DV-B", fontSize=10.4, leading=14,
                        spaceBefore=6, spaceAfter=3, textColor=INK, keepWithNext=1)
    return Paragraph(fx(t), st)


def bullets(items):
    return [Paragraph(fx(i), bul, bulletText="•") for i in items]


def steps(items):
    return [Paragraph(fx(t), bul, bulletText=f"{n}.") for n, t in enumerate(items, 1)]


def callout(title, text, key, icon=""):
    inner = [Paragraph(f"<b>{icon}{title}</b>", ParagraphStyle("ct", parent=cell, fontSize=9, textColor=ACC[key], spaceAfter=2)),
             Paragraph(fx(text), ParagraphStyle("cb", parent=cell, fontSize=9, leading=13))]
    t = Table([[inner]], colWidths=[W])
    t.setStyle(TableStyle([
        ("BACKGROUND", (0, 0), (-1, -1), LIGHT[key]),
        ("LINEBEFORE", (0, 0), (0, -1), 3.2, ACC[key]),
        ("LEFTPADDING", (0, 0), (-1, -1), 10), ("RIGHTPADDING", (0, 0), (-1, -1), 10),
        ("TOPPADDING", (0, 0), (-1, -1), 6), ("BOTTOMPADDING", (0, 0), (-1, -1), 7),
    ]))
    return [t, Spacer(1, 7)]


def chapter_header(num, title, tagline, key):
    inner = [Paragraph(f"<font color='white' size='21'><b>{num}  {title}</b></font>",
                       ParagraphStyle("chh", parent=body, leading=26, spaceAfter=3)),
             Paragraph(f"<font color='#f3f4f6' size='10'>{tagline}</font>",
                       ParagraphStyle("chs", parent=body, leading=14, spaceAfter=0))]
    t = Table([[inner]], colWidths=[W])
    t.setStyle(TableStyle([("BACKGROUND", (0, 0), (-1, -1), ACC[key]),
                           ("LEFTPADDING", (0, 0), (-1, -1), 16), ("RIGHTPADDING", (0, 0), (-1, -1), 16),
                           ("TOPPADDING", (0, 0), (-1, -1), 14), ("BOTTOMPADDING", (0, 0), (-1, -1), 14)]))
    return [t, Spacer(1, 10)]


def glance(vals, key):
    labels = ["Best case", "Average", "Worst case", "Extra space", "Stable?", "In-place?"]
    rows = [[Paragraph(f"<font color='white'><b>{l}</b></font>", ParagraphStyle("gl", parent=cellc, fontSize=8)) for l in labels],
            [Paragraph(f"<b>{fx(v)}</b>", cellc) for v in vals]]
    t = Table(rows, colWidths=[W / 6] * 6)
    t.setStyle(TableStyle([("BACKGROUND", (0, 0), (-1, 0), ACC[key]),
                           ("BACKGROUND", (0, 1), (-1, 1), LIGHT[key]),
                           ("BOX", (0, 0), (-1, -1), 0.6, ACC[key]),
                           ("INNERGRID", (0, 0), (-1, -1), 0.4, colors.white),
                           ("VALIGN", (0, 0), (-1, -1), "MIDDLE"),
                           ("TOPPADDING", (0, 0), (-1, -1), 5), ("BOTTOMPADDING", (0, 0), (-1, -1), 5)]))
    return [t, Spacer(1, 8)]


def grid_table(data, colw, key, header=True, zebra=True):
    rows = []
    for ri, r in enumerate(data):
        row = []
        for c in r:
            if isinstance(c, str):
                if header and ri == 0:
                    row.append(Paragraph(f"<font color='white'><b>{fx(c)}</b></font>", cell))
                else:
                    row.append(Paragraph(fx(c), cell))
            else:
                row.append(c)
        rows.append(row)
    t = Table(rows, colWidths=colw, repeatRows=1 if header else 0)
    st = [("BOX", (0, 0), (-1, -1), 0.6, HX("#9ca3af")),
          ("INNERGRID", (0, 0), (-1, -1), 0.3, HX("#d1d5db")),
          ("VALIGN", (0, 0), (-1, -1), "MIDDLE"),
          ("TOPPADDING", (0, 0), (-1, -1), 4), ("BOTTOMPADDING", (0, 0), (-1, -1), 4),
          ("LEFTPADDING", (0, 0), (-1, -1), 6), ("RIGHTPADDING", (0, 0), (-1, -1), 6)]
    if header:
        st.append(("BACKGROUND", (0, 0), (-1, 0), ACC[key]))
    if zebra:
        for i in range(1 if header else 0, len(rows)):
            if i % 2 == 0:
                st.append(("BACKGROUND", (0, i), (-1, i), LIGHT[key]))
    t.setStyle(TableStyle(st))
    return [t, Spacer(1, 8)]


def esc(s):
    return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")


def code_block(code, key, title="C code"):
    lines = code.strip("\n").split("\n")
    rows = []
    for ln in lines:
        m = re.match(r"^( *)(.*?)(\s*//.*)?$", ln)
        ind, main, com = m.group(1), m.group(2), m.group(3)
        html = "&nbsp;" * len(ind) + esc(main)
        if com:
            html += "&nbsp;&nbsp;<font color='#6b7280'><i>" + esc(com.strip()) + "</i></font>"
        if not html:
            html = "&nbsp;"
        rows.append([Paragraph(html, codest)])
    t = Table(rows, colWidths=[W])
    t.setStyle(TableStyle([("BACKGROUND", (0, 0), (-1, -1), HX("#f3f4f6")),
                           ("BOX", (0, 0), (-1, -1), 0.6, HX("#d1d5db")),
                           ("LINEBEFORE", (0, 0), (0, -1), 3, ACC[key]),
                           ("LEFTPADDING", (0, 0), (-1, -1), 11), ("TOPPADDING", (0, 0), (-1, -1), 0.6),
                           ("BOTTOMPADDING", (0, 0), (-1, -1), 0.6),
                           ("TOPPADDING", (0, 0), (-1, 0), 6), ("BOTTOMPADDING", (0, -1), (-1, -1), 6)]))
    return [Paragraph(f"<b>{title}</b>", ParagraphStyle("cl", parent=small, textColor=ACC[key], keepWithNext=1)), t, Spacer(1, 8)]


# ------------------------------------------------------------------ diagrams
def trace_drawing(rows, box=30, labelw=205, idx=True):
    rowh = box + 9
    n = max(len(r[1]) for r in rows)
    Wd = labelw + n * box + 4
    top_pad = 13 if idx else 2
    Hd = len(rows) * rowh + top_pad
    d = Drawing(Wd, Hd)
    if idx:
        for i in range(n):
            d.add(String(labelw + i * box + box / 2, Hd - 9, str(i), fontName="DV", fontSize=7, fillColor=HX("#6b7280"), textAnchor="middle"))
    for k, r in enumerate(rows):
        label, vals, hl = r[0], r[1], r[2]
        sep = r[3] if len(r) > 3 else []
        ytop = Hd - top_pad - k * rowh
        yb = ytop - box - 2
        parts = label.split("|")
        if len(parts) == 2:
            d.add(String(0, yb + box / 2 + 3, parts[0], fontName="DV-B", fontSize=8, fillColor=INK))
            d.add(String(0, yb + box / 2 - 8, parts[1], fontName="DV", fontSize=8, fillColor=HX("#4b5563")))
        else:
            d.add(String(0, yb + box / 2 - 3, parts[0], fontName="DV-B", fontSize=8, fillColor=INK))
        for i, v in enumerate(vals):
            x = labelw + i * box
            d.add(Rect(x, yb, box, box, fillColor=hl.get(i, colors.white), strokeColor=HX("#6b7280"), strokeWidth=0.8))
            d.add(String(x + box / 2, yb + box / 2 - 4, str(v), fontName="DV-B", fontSize=10.5 if box >= 28 else 9, fillColor=INK, textAnchor="middle"))
        for s in sep:
            x = labelw + s * box
            d.add(Line(x, yb - 3, x, yb + box + 3, strokeColor=HX("#dc2626"), strokeWidth=2.2))
    d.hAlign = "CENTER"
    return d


def legend(items, width=W):
    d = Drawing(width, 16)
    x = 0
    for col, txt in items:
        d.add(Rect(x, 3, 11, 10, fillColor=col, strokeColor=HX("#6b7280"), strokeWidth=0.6))
        d.add(String(x + 15, 5, txt, fontName="DV", fontSize=7.6, fillColor=INK))
        x += 15 + pdfmetrics.stringWidth(txt, "DV", 7.6) + 16
    d.hAlign = "CENTER"
    return d


def levels_drawing(levels, box=28, labelw=95, gapg=14):
    """levels: list of (label, groups, fill)"""
    rowh = box + 12
    Wd = W
    Hd = len(levels) * rowh
    d = Drawing(Wd, Hd)
    region = Wd - labelw
    for k, (label, groups, fill) in enumerate(levels):
        yb = Hd - (k + 1) * rowh + 6
        total = sum(len(g) for g in groups) * box + gapg * (len(groups) - 1)
        x = labelw + (region - total) / 2
        d.add(String(0, yb + box / 2 - 3, label, fontName="DV-B", fontSize=8, fillColor=INK))
        for g in groups:
            for v in g:
                d.add(Rect(x, yb, box, box, fillColor=fill, strokeColor=HX("#6b7280"), strokeWidth=0.8))
                d.add(String(x + box / 2, yb + box / 2 - 4, str(v), fontName="DV-B", fontSize=10, fillColor=INK, textAnchor="middle"))
                x += box
            x += gapg
    d.hAlign = "CENTER"
    return d


def tree(d, vals, x0, w, ytop, fills, r=15, dy=46, title=None):
    n = len(vals)
    pos = {}
    for i in range(n):
        lvl = int(math.floor(math.log2(i + 1)))
        p = i + 1 - 2 ** lvl
        pos[i] = (x0 + w * (p + 0.5) / (2 ** lvl), ytop - lvl * dy)
    for i in range(1, n):
        par = (i - 1) // 2
        d.add(Line(pos[par][0], pos[par][1], pos[i][0], pos[i][1], strokeColor=HX("#6b7280"), strokeWidth=1))
    for i in range(n):
        x, y = pos[i]
        d.add(Circle(x, y, r, fillColor=fills.get(i, TEAL), strokeColor=HX("#374151"), strokeWidth=1))
        d.add(String(x, y - 4, str(vals[i]), fontName="DV-B", fontSize=10.5, fillColor=INK, textAnchor="middle"))
        d.add(String(x + r + 2, y + r - 6, f"i={i}", fontName="DV", fontSize=6.8, fillColor=HX("#6b7280")))
    if title:
        d.add(String(x0 + w / 2, ytop + 28, title, fontName="DV-B", fontSize=8.6, fillColor=INK, textAnchor="middle"))


# ------------------------------------------------------------------ document
story = []


def footer(canv, doc):
    canv.saveState()
    canv.setFont("DV", 8)
    canv.setFillColor(HX("#6b7280"))
    canv.drawString(MARGIN, 10 * mm, "Sorting Algorithms Made Easy")
    canv.drawRightString(PAGE_W - MARGIN, 10 * mm, f"Page {doc.page}")
    canv.setStrokeColor(HX("#d1d5db"))
    canv.line(MARGIN, 14 * mm, PAGE_W - MARGIN, 14 * mm)
    canv.restoreState()


def cover_bg(canv, doc):
    canv.saveState()
    canv.setFillColor(HX("#111827"))
    canv.rect(0, PAGE_H - 95 * mm, PAGE_W, 95 * mm, stroke=0, fill=1)
    cols = [ACC[k] for k in ["bubble", "insertion", "shell", "merge", "quick", "heap", "radix"]]
    bw = PAGE_W / len(cols)
    for i, c in enumerate(cols):
        canv.setFillColor(c)
        canv.rect(i * bw, PAGE_H - 99 * mm, bw, 4 * mm, stroke=0, fill=1)
    canv.restoreState()


import os

output_dir = r"C:\Code_Practice\SoumyaCodes\DSA_DryRun"
os.makedirs(output_dir, exist_ok=True)

output_path = os.path.join(
    output_dir,
    "Sorting_Algorithms_Made_Easy.pdf"
)

doc = BaseDocTemplate(
    output_path,
    pagesize=A4,
    leftMargin=MARGIN,
    rightMargin=MARGIN,
    topMargin=16 * mm,
    bottomMargin=20 * mm,
    title="Sorting Algorithms Made Easy",
    author="Study guide"
)
frame = Frame(MARGIN, 20 * mm, W, PAGE_H - 36 * mm, id="f", leftPadding=0, rightPadding=0, topPadding=0, bottomPadding=0)
cover_frame = Frame(MARGIN, 20 * mm, W, PAGE_H - 36 * mm, id="cf", leftPadding=0, rightPadding=0, topPadding=0, bottomPadding=0)
doc.addPageTemplates([PageTemplate(id="cover", frames=[cover_frame], onPage=cover_bg),
                      PageTemplate(id="main", frames=[frame], onPage=footer)])

# ------------------------------------------------------------------ cover
story += [Spacer(1, 22 * mm),
          Paragraph("<font color='white' size='34'><b>Sorting Algorithms</b></font>", ParagraphStyle("t1", parent=body, leading=40)),
          Paragraph("<font color='#fbbf24' size='24'><b>Made Easy</b></font>", ParagraphStyle("t2", parent=body, leading=30)),
          Spacer(1, 6 * mm),
          Paragraph("<font color='#e5e7eb' size='11'>Bubble · Insertion · Shell · Merge · Quick · Heap · Radix</font>", ParagraphStyle("t3", parent=body, leading=16)),
          Paragraph("<font color='#9ca3af' size='9.5'>Plain-language explanations, step-by-step traces, diagrams and C code for every method in the syllabus.</font>", ParagraphStyle("t4", parent=body, leading=14)),
          Spacer(1, 62 * mm)]

story.append(Paragraph("<b>How every chapter is organised</b>", ParagraphStyle("hh", parent=body, fontName="DV-B", fontSize=12, textColor=INK)))
story += bullets([
    "<b>The big idea</b> – the whole algorithm in two or three sentences, plus a real-life analogy.",
    "<b>Step-by-step rules</b> – what the algorithm does, in numbered steps.",
    "<b>Worked example</b> – a coloured trace so you can watch the array change.",
    "<b>C code</b> – a short, clean implementation you can write in the exam.",
    "<b>Complexity and properties</b> – time, space, stable, in-place, and <i>why</i> the numbers come out that way.",
    "<b>When to use it</b> – strengths, weaknesses and exam tips.",
])
story.append(Spacer(1, 4 * mm))
story.append(Paragraph("<b>Contents</b>", ParagraphStyle("hh2", parent=body, fontName="DV-B", fontSize=12, textColor=INK)))
toc = [["Part", "Topic"],
       ["0", "Sorting basics, key terms and Big-O in 30 seconds"],
       ["1", "Bubble Sort"], ["2", "Insertion Sort"], ["3", "Shell Sort"], ["4", "Merge Sort"],
       ["5", "Quick Sort"], ["6", "Heap Sort"], ["7", "Radix Sort"],
       ["8", "Comparison table, cheat sheet and likely exam questions"]]
story += grid_table(toc, [30 * mm, W - 30 * mm], "intro")
story += [NextPageTemplate("main"), PageBreak()]

# ------------------------------------------------------------------ part 0
story += chapter_header("0", "Sorting Basics", "Everything you need to understand before the seven algorithms", "intro")
story.append(P("<b>Sorting</b> means arranging items in a fixed order – usually smallest to largest (ascending) or largest to smallest (descending). It matters because sorted data is much easier to work with: you can search it quickly with binary search, find duplicates, merge lists and produce rankings. Think of a dictionary – it is only usable because the words are sorted."))
story.append(H2("Words you must know", "intro"))
terms = [["Term", "Meaning", "Tiny example"],
         ["Pass", "One full sweep over the data (or over the unsorted part).", "Bubble sort's first pass pushes the largest value to the end."],
         ["Comparison-based", "Decides the order only by comparing two elements at a time.", "Bubble, insertion, shell, merge, quick, heap. (Radix is <b>not</b>.)"],
         ["In-place", "Sorts using only a constant amount of extra memory, O(1).", "Bubble, insertion, heap sort rearrange the same array."],
         ["Stable", "Equal elements keep their original relative order.", "Sorting students by marks: two students with 80 stay in the same order as before."],
         ["Adaptive", "Runs faster if the input is already nearly sorted.", "Insertion sort on [1,2,3,5,4] needs very few moves."],
         ["Divide and conquer", "Split the problem, solve the parts, combine the answers.", "Merge sort and quick sort."],
         ["Internal vs external", "Internal: all data fits in RAM. External: data is on disk and is sorted in chunks.", "Merge sort is the standard choice for external sorting."]]
story += grid_table(terms, [30 * mm, 70 * mm, W - 100 * mm], "intro")
story.append(H2("Big-O in 30 seconds", "intro"))
story.append(P("Big-O tells you how the running time <i>grows</i> when the number of items <b>n</b> grows. Do not worry about exact seconds – compare the growth. Suppose n = 1000:"))
story += grid_table([["Growth", "Name", "Steps for n = 1000", "Which sorts?"],
                     ["O(n)", "Linear", "about 1,000", "Best case of bubble and insertion"],
                     ["O(n log n)", "Linearithmic", "about 10,000", "Merge, heap, quick (average)"],
                     ["O(n^2)", "Quadratic", "about 1,000,000", "Bubble, insertion (average and worst)"]],
                    [28 * mm, 30 * mm, 42 * mm, W - 100 * mm], "intro")
story += callout("Why O(n log n) is the magic number",
                 "Any sorting method that works <b>only by comparing elements</b> needs at least about n log n comparisons in the worst case. That is why merge, heap and quick sort are considered the &quot;fast&quot; comparison sorts. Radix sort escapes this limit only because it does <i>not</i> compare whole elements – it looks at digits.", "intro")
story.append(H2("Roadmap of the seven methods", "intro"))
story += grid_table([["Method", "One-line idea", "Family"],
                     ["Bubble", "Swap neighbours that are out of order; big values float to the end.", "Simple, O(n^2)"],
                     ["Insertion", "Take the next item and slide it into the sorted part on the left.", "Simple, O(n^2)"],
                     ["Shell", "Insertion sort on items far apart first, then closer and closer.", "Improved insertion"],
                     ["Merge", "Split in halves, sort each, then merge two sorted halves.", "Divide and conquer"],
                     ["Quick", "Pick a pivot; smaller values go left, larger go right; repeat.", "Divide and conquer"],
                     ["Heap", "Build a max-heap, then keep removing the biggest element.", "Selection with a heap"],
                     ["Radix", "Sort digit by digit, from the last digit to the first.", "Non-comparison"]],
                    [24 * mm, W - 24 * mm - 38 * mm, 38 * mm], "intro")

# ------------------------------------------------------------------ 1 bubble
K = "bubble"
story.append(PageBreak())
story += chapter_header("1", "Bubble Sort", "Compare neighbours, swap if wrong – the biggest value bubbles to the end", K)
story.append(H2("The big idea", K))
story.append(P("Walk through the array from left to right. Each time, look at two <b>neighbouring</b> elements. If the left one is bigger than the right one, swap them. When you reach the end, the <b>largest</b> element has been carried all the way to the last position – just like an air bubble rising to the surface of water. Then repeat the walk for the remaining unsorted part."))
story += callout("Real-life analogy",
                 "Students stand in a line and the teacher walks along it. Whenever a taller student stands before a shorter one, the teacher swaps them. After one walk the tallest student is at the end of the line. After a few walks the whole line is in height order.", K, "💡 ")
story.append(H2("Step-by-step rules", K))
story += steps([
    "Start at the first element. Compare <b>arr[j]</b> with <b>arr[j+1]</b>.",
    "If arr[j] &gt; arr[j+1], swap them. Otherwise leave them.",
    "Move one step right and repeat until you reach the end of the unsorted part. This is <b>one pass</b>; the largest remaining value is now in its final place.",
    "Repeat passes. Each pass can stop one position earlier because the tail is already sorted.",
    "<b>Optimisation:</b> if a whole pass makes <b>no swap</b>, the array is sorted – stop early.",
])
story.append(H2("Worked example:  5, 1, 4, 2, 8", K))
rows = [
    ("Start", [5, 1, 4, 2, 8], {}),
    ("Pass 1|compare 5 and 1 → swap", [1, 5, 4, 2, 8], {0: BLUE, 1: BLUE}),
    ("Pass 1|compare 5 and 4 → swap", [1, 4, 5, 2, 8], {1: BLUE, 2: BLUE}),
    ("Pass 1|compare 5 and 2 → swap", [1, 4, 2, 5, 8], {2: BLUE, 3: BLUE}),
    ("Pass 1|compare 5 and 8 → no swap", [1, 4, 2, 5, 8], {3: AMBER, 4: AMBER}),
    ("End of pass 1|8 is now in place", [1, 4, 2, 5, 8], {4: GREEN}),
    ("Pass 2|4↔2 swapped; others fine", [1, 2, 4, 5, 8], {3: GREEN, 4: GREEN}),
    ("Pass 3|no swaps at all → stop", [1, 2, 4, 5, 8], {i: GREEN for i in range(5)}),
]
story.append(KeepTogether([trace_drawing(rows), Spacer(1, 3),
                           legend([(BLUE, "swapped"), (AMBER, "compared, no swap"), (GREEN, "final position")]),
                           P("Figure 1 – Bubble sort on five numbers. Notice how 8 is already at the end after pass 1.", cap)]))
story.append(H2("C code", K))
story += code_block("""
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {          // number of passes
        int swapped = 0;                        // optimisation flag
        for (int j = 0; j < n - i - 1; j++) {   // tail is already sorted
            if (arr[j] > arr[j + 1]) {          // neighbours out of order?
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) break;                // no swap => sorted
    }
}
""", K)
story.append(H2("Complexity and properties", K))
story += glance(["O(n)", "O(n^2)", "O(n^2)", "O(1)", "Yes", "Yes"], K)
story += bullets([
    "<b>Why O(n<super>2</super>)?</b> There are about n passes and each pass makes up to n comparisons: (n−1) + (n−2) + … + 1 = n(n−1)/2 comparisons.",
    "<b>Why best case O(n)?</b> On an already sorted array the first pass makes no swap, the flag stops the loop, and only n−1 comparisons were done. (Without the flag the best case is still O(n<super>2</super>).)",
    "<b>Stable</b> because we swap only when arr[j] is <i>strictly</i> greater – equal elements are never swapped.",
])
story += callout("When to use it / exam tip",
                 "Bubble sort is easy to write and understand, but it is slow – it is used for teaching and for tiny or nearly sorted lists. Remember: <b>after pass k, the k largest elements are in their final positions.</b> Many exam questions ask for the array &quot;after the 2nd pass&quot;.", K, "★ ")

# ------------------------------------------------------------------ 2 insertion
K = "insertion"
story.append(PageBreak())
story += chapter_header("2", "Insertion Sort", "Grow a sorted section by inserting one new item at a time", K)
story.append(H2("The big idea", K))
story.append(P("Divide the array into two parts: a <b>sorted part</b> on the left (at the start it holds just the first element) and an <b>unsorted part</b> on the right. Take the first element of the unsorted part – call it the <b>key</b> – and slide it left into the correct place inside the sorted part, shifting bigger elements one step to the right to make room."))
story += callout("Real-life analogy",
                 "This is exactly how most people sort playing cards in their hand. You pick up one new card at a time and slide it into the right spot among the cards you already hold, which are already in order.", K, "💡 ")
story.append(H2("Step-by-step rules", K))
story += steps([
    "Treat arr[0] as a sorted section of size 1.",
    "For i = 1 to n−1: store arr[i] in <b>key</b>.",
    "Look at the sorted section from right to left. While the element is <b>greater than key</b>, shift it one place to the right.",
    "Put key into the gap that was created.",
    "After the last element is inserted, the whole array is sorted.",
])
story.append(H2("Worked example:  5, 2, 4, 6, 1, 3", K))
rows = [
    ("Start|first element is 'sorted'", [5, 2, 4, 6, 1, 3], {0: GREEN}),
    ("key = 2|2 jumps in front of 5", [2, 5, 4, 6, 1, 3], {0: ORANGE, 1: GREEN}),
    ("key = 4|4 goes before 5", [2, 4, 5, 6, 1, 3], {0: GREEN, 1: ORANGE, 2: GREEN}),
    ("key = 6|already in place", [2, 4, 5, 6, 1, 3], {0: GREEN, 1: GREEN, 2: GREEN, 3: ORANGE}),
    ("key = 1|moves all the way to front", [1, 2, 4, 5, 6, 3], {0: ORANGE, 1: GREEN, 2: GREEN, 3: GREEN, 4: GREEN}),
    ("key = 3|goes between 2 and 4", [1, 2, 3, 4, 5, 6], {0: GREEN, 1: GREEN, 2: ORANGE, 3: GREEN, 4: GREEN, 5: GREEN}),
]
story.append(KeepTogether([trace_drawing(rows), Spacer(1, 3),
                           legend([(ORANGE, "key just inserted"), (GREEN, "sorted part")]),
                           P("Figure 2 – The green block grows by one element every step.", cap)]))
story.append(H2("C code", K))
story += code_block("""
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];            // element to insert
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];     // shift bigger element right
            j--;
        }
        arr[j + 1] = key;            // drop key into the gap
    }
}
""", K)
story.append(H2("Complexity and properties", K))
story += glance(["O(n)", "O(n^2)", "O(n^2)", "O(1)", "Yes", "Yes"], K)
story += bullets([
    "<b>Best case O(n):</b> if the array is already sorted, the while loop never runs, so each element costs just one comparison.",
    "<b>Worst case O(n<super>2</super>):</b> a reverse-sorted array – each key must travel all the way to the front, giving 1 + 2 + … + (n−1) shifts.",
    "<b>Adaptive and stable:</b> it stops shifting as soon as it finds an element ≤ key, so equal elements never cross each other.",
    "<b>Online:</b> it can sort data as it arrives, one element at a time.",
])
story += callout("When to use it / exam tip",
                 "Excellent for <b>small arrays</b> and <b>nearly sorted data</b>. Real libraries (for example the hybrid sorts inside many languages) use insertion sort for small chunks. Bubble and insertion are both O(n<super>2</super>) but insertion sort usually does fewer operations because it <i>shifts</i> instead of swapping repeatedly.", K, "★ ")

# ------------------------------------------------------------------ 3 shell
K = "shell"
story.append(PageBreak())
story += chapter_header("3", "Shell Sort", "Insertion sort with long jumps – fix far-apart items first", K)
story.append(H2("The big idea", K))
story.append(P("Insertion sort is slow when a small value sits far to the right, because it can only move <b>one position at a time</b>. Shell sort fixes this. It first runs insertion sort on elements that are <b>gap</b> positions apart (for example every 4th element), then reduces the gap (4 → 2 → 1) and repeats. Early passes move elements across large distances; by the time the gap is 1 the array is <i>almost sorted</i>, and a normal insertion sort finishes very quickly."))
story += callout("Real-life analogy",
                 "Imagine tidying a messy bookshelf. First you swap books that are far from their correct section (big moves). Then you fine-tune neighbouring books (small moves). Rough sorting first, fine sorting last.", K, "💡 ")
story.append(H2("Step-by-step rules", K))
story += steps([
    "Choose a starting gap, usually <b>n/2</b>.",
    "For this gap, treat elements gap apart as separate small lists (e.g. gap 4 → positions 0,4 / 1,5 / 2,6 / 3,7) and sort each list with insertion sort. The array is now called <b>gap-sorted</b>.",
    "Halve the gap (gap = gap/2) and repeat step 2.",
    "Continue until gap = 1. The last pass is an ordinary insertion sort on a nearly sorted array – very fast.",
])
story.append(H2("Worked example:  35, 33, 42, 10, 14, 19, 27, 44   (n = 8)", K))
story.append(P("The gaps used are 4, 2, 1. In the first row, items with the <i>same colour</i> belong to the same gap-4 list and are insertion-sorted among themselves."))
g4 = [BLUE, GREEN, AMBER, PINK]
rows = [
    ("Start|colour = gap-4 groups", [35, 33, 42, 10, 14, 19, 27, 44], {i: g4[i % 4] for i in range(8)}),
    ("After gap = 4|(35,14)(33,19)(42,27)(10,44)", [14, 19, 27, 10, 35, 33, 42, 44], {i: g4[i % 4] for i in range(8)}),
    ("Now gap = 2|colour = gap-2 groups", [14, 19, 27, 10, 35, 33, 42, 44], {i: (PURPLE if i % 2 == 0 else TEAL) for i in range(8)}),
    ("After gap = 2|evens already ordered, odds fixed", [14, 10, 27, 19, 35, 33, 42, 44], {i: (PURPLE if i % 2 == 0 else TEAL) for i in range(8)}),
    ("After gap = 1|ordinary insertion sort", [10, 14, 19, 27, 33, 35, 42, 44], {i: GREEN for i in range(8)}),
]
story.append(KeepTogether([trace_drawing(rows, labelw=215), Spacer(1, 3),
                           P("Figure 3 – Shell sort with gaps 4, 2, 1. After the gap-4 and gap-2 passes the array is already close to sorted, so the final pass moves things only a short distance.", cap)]))
story.append(H2("C code", K))
story += code_block("""
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {      // shrink the gap
        for (int i = gap; i < n; i++) {             // insertion sort with step = gap
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];              // shift by gap, not by 1
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
""", K)
story.append(H2("Gap sequences – the speed depends on them", K))
story += grid_table([["Sequence", "Gaps (example)", "Worst-case time"],
                     ["Shell's original (n/2, n/4, … 1)", "8, 4, 2, 1", "O(n^2)"],
                     ["Hibbard (2^k − 1)", "1, 3, 7, 15, 31 …", "O(n^1.5)"],
                     ["Knuth ((3^k − 1)/2)", "1, 4, 13, 40, 121 …", "O(n^1.5)"],
                     ["Sedgewick", "1, 5, 19, 41, 109 …", "O(n<super>4/3</super>)"]],
                    [62 * mm, 55 * mm, W - 117 * mm], K)
story.append(H2("Complexity and properties", K))
story += glance(["O(n log n)", "≈ O(n^1.5)", "O(n^2)", "O(1)", "No", "Yes"], K)
story += bullets([
    "<b>Average case</b> depends on the gap sequence; with good sequences it is far better than O(n<super>2</super>) but there is no single simple formula.",
    "<b>Not stable:</b> moving an element by a large gap can jump it over an equal element.",
    "<b>In-place and simple:</b> no recursion and no extra array – the reason Shell sort is popular in embedded systems.",
])
story += callout("When to use it / exam tip",
                 "Shell sort = <b>insertion sort + gaps</b>. A very common exam question is &quot;how does Shell sort improve insertion sort?&quot; – answer: it allows elements to move long distances early, so the final gap-1 pass has very little work to do.", K, "★ ")

# ------------------------------------------------------------------ 4 merge
K = "merge"
story.append(PageBreak())
story += chapter_header("4", "Merge Sort", "Divide the array in halves, sort each half, then merge", K)
story.append(H2("The big idea", K))
story.append(P("Merge sort is a <b>divide and conquer</b> algorithm. A list of one element is already sorted, and <b>two sorted lists can be merged into one sorted list very cheaply</b>. So: keep splitting the array in half until every piece has one element, then keep merging pieces back together in sorted order."))
story += callout("Real-life analogy",
                 "Two friends each hold a sorted pile of exam papers. To combine them, repeatedly compare the top paper of each pile and place the smaller one on a new pile. When one pile runs out, put the rest of the other pile on top. That is the <b>merge</b> step.", K, "💡 ")
story.append(H2("Step-by-step rules", K))
story += steps([
    "<b>Divide:</b> find the middle, split the array into a left half and a right half.",
    "<b>Conquer:</b> recursively sort the left half and the right half.",
    "<b>Combine:</b> merge the two sorted halves into one sorted array using the merge procedure.",
    "<b>Base case:</b> an array with 0 or 1 element is already sorted – stop splitting.",
])
story.append(H2("Worked example:  38, 27, 43, 3, 9, 82, 10", K))
div = [("Original", [[38, 27, 43, 3, 9, 82, 10]], BLUE),
       ("Split 1", [[38, 27, 43, 3], [9, 82, 10]], BLUE),
       ("Split 2", [[38, 27], [43, 3], [9, 82], [10]], BLUE),
       ("Split 3", [[38], [27], [43], [3], [9], [82], [10]], BLUE),
       ("Merge 1", [[27, 38], [3, 43], [9, 82], [10]], GREEN),
       ("Merge 2", [[3, 27, 38, 43], [9, 10, 82]], GREEN),
       ("Merge 3", [[3, 9, 10, 27, 38, 43, 82]], GREEN)]
story.append(KeepTogether([levels_drawing(div), Spacer(1, 3),
                           legend([(BLUE, "dividing phase (going down)"), (GREEN, "merging phase (coming back up)")]),
                           P("Figure 4 – The recursion tree. Each group is a sub-array. The array is cut in half until single elements remain, then merged upward in sorted order.", cap)]))
story.append(H3("The merge step in detail", K))
story.append(P("Merge Left = [3, 27, 38, 43] and Right = [9, 10, 82]. Keep one pointer in each list; always copy the smaller front value into the output."))
story += grid_table([["Step", "Compare", "Smaller → copied", "Output so far"],
                     ["1", "3 vs 9", "3 (left)", "3"],
                     ["2", "27 vs 9", "9 (right)", "3, 9"],
                     ["3", "27 vs 10", "10 (right)", "3, 9, 10"],
                     ["4", "27 vs 82", "27 (left)", "3, 9, 10, 27"],
                     ["5", "38 vs 82", "38 (left)", "3, 9, 10, 27, 38"],
                     ["6", "43 vs 82", "43 (left)", "3, 9, 10, 27, 38, 43"],
                     ["7", "left list empty", "copy remaining 82", "3, 9, 10, 27, 38, 43, 82"]],
                    [16 * mm, 38 * mm, 48 * mm, W - 102 * mm], K)
story.append(H2("C code", K))
story += code_block("""
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));     // temporary copies
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {                    // pick the smaller front value
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else              arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];             // copy leftovers
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;                  // middle index
        mergeSort(arr, l, m);                     // sort left half
        mergeSort(arr, m + 1, r);                 // sort right half
        merge(arr, l, m, r);                      // combine
    }
}
""", K)
story.append(H2("Complexity and properties", K))
story += glance(["O(n log n)", "O(n log n)", "O(n log n)", "O(n)", "Yes", "No"], K)
story += bullets([
    "<b>Why n log n?</b> Halving n repeatedly gives about log<sub>2</sub> n levels. At every level the merge steps together touch all n elements once. So the work is n × log n – in <i>every</i> case, because the splitting never depends on the data. Recurrence: T(n) = 2T(n/2) + n.",
    "<b>Extra space O(n):</b> the temporary arrays L and R are needed during merging, so merge sort is <i>not</i> in-place.",
    "<b>Stable:</b> using L[i] &lt;= R[j] (not &lt;) takes the left element first when values are equal.",
])
story += callout("When to use it / exam tip",
                 "Guaranteed O(n log n) and stable – great for <b>linked lists</b> and <b>external sorting</b> (huge files on disk). Its drawback is the extra memory. Exam favourites: draw the recursion tree, show the merge of two lists, and state T(n) = 2T(n/2) + n.", K, "★ ")

# ------------------------------------------------------------------ 5 quick
K = "quick"
story.append(PageBreak())
story += chapter_header("5", "Quick Sort", "Choose a pivot, partition around it, repeat on both sides", K)
story.append(H2("The big idea", K))
story.append(P("Quick sort is also <b>divide and conquer</b>, but the hard work is done <i>before</i> the recursion instead of after. Pick one element as the <b>pivot</b>. Rearrange the array (this is called <b>partitioning</b>) so that everything smaller than the pivot is on its left and everything larger is on its right. The pivot is now in its <b>final sorted position</b>. Then sort the left part and the right part the same way."))
story += callout("Real-life analogy",
                 "Line students up by height. Pick one student as the reference. Everyone shorter goes to the left of the reference, everyone taller goes to the right. The reference student is now in the correct place for good. Repeat the idea separately for the left group and the right group.", K, "💡 ")
story.append(H2("Step-by-step rules (Lomuto partition, pivot = last element)", K))
story += steps([
    "Choose the pivot = last element of the current range. Keep a marker <b>i</b> just before the range.",
    "Scan j from the start of the range up to (but not including) the pivot.",
    "If arr[j] ≤ pivot: move marker i one step right and <b>swap arr[i] with arr[j]</b>. This grows the &quot;small values&quot; zone.",
    "After the scan, swap the pivot with arr[i+1]. The pivot is now in its final place; return its index.",
    "Recursively quick-sort the part left of the pivot and the part right of the pivot.",
])
story.append(H2("Worked example:  8, 3, 1, 7, 0, 10, 2", K))
story.append(P("<b>First partition</b> – pivot is the last element, <b>2</b>. Only the scans that cause a swap are shown (for 8, 3, 7 and 10 nothing happens because they are bigger than 2)."))
rows = [
    ("Start|pivot = 2", [8, 3, 1, 7, 0, 10, 2], {6: PINK}),
    ("j sees 1 (≤ 2)|swap arr[0] ↔ arr[2]", [1, 3, 8, 7, 0, 10, 2], {0: BLUE, 2: BLUE, 6: PINK}),
    ("j sees 0 (≤ 2)|swap arr[1] ↔ arr[4]", [1, 0, 8, 7, 3, 10, 2], {1: BLUE, 4: BLUE, 6: PINK}),
    ("Finish|swap pivot ↔ arr[2]", [1, 0, 2, 7, 3, 10, 8], {2: GREEN}, [2, 3]),
]
story.append(KeepTogether([trace_drawing(rows, labelw=195), Spacer(1, 3),
                           legend([(PINK, "pivot"), (BLUE, "swapped"), (GREEN, "pivot in final place")]),
                           P("Figure 5 – First partition. The red bars mark the pivot's final position: smaller values on its left, larger on its right.", cap)]))
story.append(P("<b>Recursion on the two parts</b> – each part is partitioned the same way:"))
rows = [
    ("After partition 1|pivot 2 fixed", [1, 0, 2, 7, 3, 10, 8], {2: GREEN}),
    ("Left part [1,0]|pivot 0 → [0,1]", [0, 1, 2, 7, 3, 10, 8], {0: GREEN, 1: GREEN, 2: GREEN}),
    ("Right part [7,3,10,8]|pivot 8 fixed", [0, 1, 2, 7, 3, 8, 10], {0: GREEN, 1: GREEN, 2: GREEN, 5: GREEN, 6: GREEN}),
    ("Part [7,3]|pivot 3 → [3,7]", [0, 1, 2, 3, 7, 8, 10], {i: GREEN for i in range(7)}),
]
story.append(KeepTogether([trace_drawing(rows, labelw=195), Spacer(1, 3),
                           P("Figure 6 – Every green box is a value that has reached its final position. The array is sorted when all boxes are green.", cap)]))
story.append(H2("C code", K))
story += code_block("""
void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];                // pivot = last element
    int i = low - 1;                      // boundary of the "small" zone
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);       // move small value into the zone
        }
    }
    swap(&arr[i + 1], &arr[high]);        // put pivot in its final place
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);       // left of pivot
        quickSort(arr, p + 1, high);      // right of pivot
    }
}
""", K)
story.append(H2("Complexity and properties", K))
story += glance(["O(n log n)", "O(n log n)", "O(n^2)", "O(log n)", "No", "Yes"], K)
story += bullets([
    "<b>Best / average case:</b> the pivot splits the array into two roughly equal parts, giving log n levels with n work each → O(n log n).",
    "<b>Worst case O(n<super>2</super>):</b> the pivot is always the smallest or largest element (for example, an already sorted array with the last element as pivot). One side is empty, the other has n−1 elements, so we get n levels with up to n work each.",
    "<b>Extra space O(log n):</b> only the recursion stack (O(n) in the worst case).",
    "<b>Not stable:</b> the long-distance swaps can change the order of equal elements.",
])
story.append(H3("Choosing the pivot", K))
story += grid_table([["Strategy", "Idea", "Comment"],
                     ["First or last element", "Simplest to code", "Worst case on sorted or reverse-sorted input"],
                     ["Random element", "Pick a random index and swap it to the end", "Makes the worst case extremely unlikely"],
                     ["Median of three", "Median of first, middle and last", "Good protection on sorted input"]],
                    [38 * mm, 62 * mm, W - 100 * mm], K)
story += callout("When to use it / exam tip",
                 "In practice quick sort is usually the <b>fastest</b> general-purpose sort: it works in-place, has a small constant factor and is cache friendly. Remember the contrast with merge sort – <b>merge sort divides trivially and works hard when combining; quick sort works hard when dividing (partition) and combining costs nothing.</b>", K, "★ ")

# ------------------------------------------------------------------ 6 heap
K = "heap"
story.append(PageBreak())
story += chapter_header("6", "Heap Sort", "Build a max-heap, then repeatedly take out the largest element", K)
story.append(H2("First, what is a heap?", K))
story.append(P("A <b>binary heap</b> is a <b>complete binary tree</b> (all levels full except possibly the last, which fills from the left) that obeys the <b>heap property</b>. In a <b>max-heap</b> every parent is greater than or equal to its children, so the <b>largest element is always at the root</b>. A heap is stored in a plain array – no pointers needed. For the element at index <b>i</b> (0-based):"))
story += grid_table([["Relation", "Index formula", "Example for node 5 at i = 1 in [10, 5, 3, 4, 1]"],
                     ["Parent", "(i − 1) / 2", "(1 − 1)/2 = 0 → value 10"],
                     ["Left child", "2i + 1", "2(1) + 1 = 3 → value 4"],
                     ["Right child", "2i + 2", "2(1) + 2 = 4 → value 1"]],
                    [28 * mm, 38 * mm, W - 66 * mm], K)
story.append(H2("The big idea", K))
story.append(P("Heap sort uses the fact that the biggest value is always at the root. It works in two phases:"))
story += steps([
    "<b>Build a max-heap</b> from the unsorted array. Start from the last non-leaf node (index n/2 − 1) and move up to the root, fixing each node with <b>heapify</b>.",
    "<b>Repeat n−1 times:</b> swap the root (current maximum) with the last element of the heap, shrink the heap size by 1 (that last position is now sorted), and <b>heapify the root</b> to restore the heap property.",
])
story += callout("Real-life analogy",
                 "Think of a tournament that always keeps the strongest player at the top of the bracket. Take the champion out and place them at the end of the results list, then re-run the bracket to find the next champion. Repeat until everyone is placed.", K, "💡 ")
story.append(H3("What is heapify (sift-down)?", K))
story.append(P("Heapify fixes a single node whose children are already valid heaps: compare the node with its two children, and if a child is larger, <b>swap with the larger child</b>. Then continue the same check at the child's position, until the node is bigger than both children or becomes a leaf."))
story.append(H2("Worked example:  4, 10, 3, 5, 1", K))
story.append(P("<b>Phase 1 – build the heap.</b> The last non-leaf node is index 1 (value 10); its children 5 and 1 are smaller, so nothing changes. Then at the root: 4 is smaller than its larger child 10, so swap; 4 now sits at index 1 where its children are 5 and 1, so swap with 5."))
dtree = Drawing(W, 150)
tree(dtree, [4, 10, 3, 5, 1], 0, W / 2 - 10, 112, {0: PINK}, title="Before (4 breaks the heap rule)")
tree(dtree, [10, 5, 3, 4, 1], W / 2 + 10, W / 2 - 10, 112, {0: GREEN, 1: BLUE, 3: BLUE}, title="After build-heap (valid max-heap)")
dtree.hAlign = "CENTER"
story.append(KeepTogether([dtree, P("Figure 7 – Phase 1 as trees. Every parent is now at least as big as its children.", cap)]))
story.append(P("<b>Phase 2 – sort.</b> Green means &quot;already in final position&quot;. The heap is the part on the left."))
rows = [
    ("Max-heap built", [10, 5, 3, 4, 1], {}),
    ("Swap root 10 ↔ last", [1, 5, 3, 4, 10], {4: GREEN, 0: BLUE}),
    ("Heapify (size 4)", [5, 4, 3, 1, 10], {4: GREEN}),
    ("Swap root 5 ↔ last", [1, 4, 3, 5, 10], {3: GREEN, 4: GREEN, 0: BLUE}),
    ("Heapify (size 3)", [4, 1, 3, 5, 10], {3: GREEN, 4: GREEN}),
    ("Swap root 4 ↔ last", [3, 1, 4, 5, 10], {2: GREEN, 3: GREEN, 4: GREEN, 0: BLUE}),
    ("Swap root 3 ↔ last", [1, 3, 4, 5, 10], {i: GREEN for i in range(5)}),
]
story.append(KeepTogether([trace_drawing(rows, labelw=170), Spacer(1, 3),
                           legend([(BLUE, "swapped root (after swap)"), (GREEN, "sorted – final position")]),
                           P("Figure 8 – The sorted region grows from the right while the heap shrinks on the left. (After the heap shrinks to size 2, [3,1] already obeys the heap rule, so heapify changes nothing.)", cap)]))
story.append(H2("C code", K))
story += code_block("""
void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void heapify(int arr[], int n, int i) {      // sift-down node i in a heap of size n
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])   largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {                         // a child is bigger: swap and continue
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)        // phase 1: build max-heap
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {           // phase 2: extract maximum
        swap(&arr[0], &arr[i]);                 // move max to its final position
        heapify(arr, i, 0);                     // restore heap on the smaller heap
    }
}
""", K)
story.append(H2("Complexity and properties", K))
story += glance(["O(n log n)", "O(n log n)", "O(n log n)", "O(1)", "No", "Yes"], K)
story += bullets([
    "<b>Phase 1 costs O(n):</b> most nodes are near the bottom and sink very little. The total work of building a heap is linear.",
    "<b>Phase 2 costs O(n log n):</b> n−1 extractions, and each heapify walks down at most the height of the tree, which is log n.",
    "<b>Not stable:</b> swapping the root with the last element jumps equal values over each other.",
    "<b>Ascending order needs a max-heap</b> (biggest goes to the back). Use a min-heap if you want to repeatedly pull out the smallest instead.",
])
story += callout("When to use it / exam tip",
                 "Heap sort gives a <b>guaranteed O(n log n)</b> like merge sort <i>and</i> uses O(1) extra space like quick sort – the best of both on paper. In practice it is slower than quick sort because of poor cache behaviour. Heaps are also the basis of <b>priority queues</b>.", K, "★ ")

# ------------------------------------------------------------------ 7 radix
K = "radix"
story.append(PageBreak())
story += chapter_header("7", "Radix Sort", "Sort numbers digit by digit – no comparisons between numbers", K)
story.append(H2("The big idea", K))
story.append(P("All the earlier methods compare two numbers directly. Radix sort never does. Instead it sorts the numbers by <b>one digit at a time</b>, starting from the <b>least significant digit</b> (units), then tens, then hundreds, and so on. For each digit it uses a <b>stable</b> sort (usually counting sort) that drops numbers into ten buckets 0–9 and collects them back in order."))
story += callout("Real-life analogy",
                 "A post office sorts letters by PIN code. First everything is put into 10 boxes by the last digit, the boxes are emptied in order 0 to 9, and the letters are re-sorted by the second-last digit, and so on. After the first digit has been processed everywhere, the letters are fully in order.", K, "💡 ")
story.append(H2("Step-by-step rules (LSD radix sort)", K))
story += steps([
    "Find the largest number to know how many digits (<b>d</b>) there are.",
    "For each digit position, starting at units: distribute the numbers into buckets 0–9 by that digit, then collect the buckets in order 0 → 9 – keeping the <b>original relative order</b> inside every bucket (stability).",
    "Move to the next digit (tens, hundreds, …) and repeat.",
    "After the last digit pass, the array is completely sorted.",
])
story.append(callout("Why must the digit-sort be stable?",
                     "When we sort by the tens digit, two numbers with the same tens digit must stay in the order the <i>units</i> pass gave them. Stability carries the earlier work forward; without it radix sort would give wrong answers.", K, "⚠ ")[0])
story.append(Spacer(1, 7))
story.append(H2("Worked example:  170, 45, 75, 90, 802, 24, 2, 66", K))
story.append(P("The largest number, 802, has 3 digits, so three passes are needed. The table shows which numbers fall into each bucket (in the order they arrive):"))
story += grid_table([["Bucket", "Pass 1 – units digit", "Pass 2 – tens digit", "Pass 3 – hundreds digit"],
                     ["0", "170, 90", "802, 2", "2, 24, 45, 66, 75, 90"],
                     ["1", "–", "–", "170"],
                     ["2", "802, 2", "24", "–"],
                     ["3", "–", "–", "–"],
                     ["4", "24", "45", "–"],
                     ["5", "45, 75", "–", "–"],
                     ["6", "66", "66", "–"],
                     ["7", "–", "170, 75", "–"],
                     ["8", "–", "–", "802"],
                     ["9", "–", "90", "–"]],
                    [20 * mm, (W - 20 * mm) / 3, (W - 20 * mm) / 3, (W - 20 * mm) / 3], K)
rows = [
    ("Input", [170, 45, 75, 90, 802, 24, 2, 66], {}),
    ("After pass 1|sorted by units digit", [170, 90, 802, 2, 24, 45, 75, 66], {}),
    ("After pass 2|sorted by tens digit", [802, 2, 24, 45, 66, 170, 75, 90], {}),
    ("After pass 3|sorted by hundreds digit", [2, 24, 45, 66, 75, 90, 170, 802], {i: GREEN for i in range(8)}),
]
story.append(KeepTogether([trace_drawing(rows, box=38, labelw=170), Spacer(1, 3),
                           P("Figure 9 – The array after every pass. After pass 2 the numbers are correctly ordered by their last two digits; after pass 3 by all digits.", cap)]))
story.append(H3("How counting sort does each pass", K))
story.append(P("For one digit position: (1) <b>count</b> how many numbers have each digit 0–9; (2) turn the counts into <b>running totals</b> – each total says where that digit's group ends in the output; (3) walk the input from <b>right to left</b>, place each number at its position and decrease that count. Walking right to left is what keeps the sort stable."))
story.append(H2("C code", K))
story += code_block("""
#include <stdlib.h>

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {       // stable sort on one digit
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;             // 1) count digits
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];                 // 2) running totals
    for (int i = n - 1; i >= 0; i--) {            // 3) place, right to left
        int d = (arr[i] / exp) % 10;
        output[count[d] - 1] = arr[i];
        count[d]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10)   // units, tens, hundreds ...
        countSort(arr, n, exp);
}
""", K)
story.append(H2("Complexity and properties", K))
story += glance(["O(d(n+k))", "O(d(n+k))", "O(d(n+k))", "O(n+k)", "Yes", "No"], K)
story += bullets([
    "<b>Notation:</b> n = number of items, d = number of digits in the largest number, k = base (10 for decimal digits).",
    "<b>Why linear-like?</b> Each pass costs O(n + k) and there are d passes. If d is small and fixed, the running time is effectively O(n) – faster than the n log n comparison limit.",
    "<b>Not in-place:</b> needs an output array of size n plus the count array.",
    "<b>Limits:</b> works on integers or fixed-length keys (strings, dates). It is not suited to arbitrary real numbers or when d is very large compared with log n.",
])
story += callout("When to use it / exam tip",
                 "Use radix sort for <b>large lists of integers with a limited number of digits</b> – phone numbers, PIN codes, IDs. Exam keywords: <b>non-comparison</b>, <b>stable</b>, <b>LSD first</b>, <b>buckets 0–9</b>, O(d(n+k)).", K, "★ ")

# ------------------------------------------------------------------ 8 final
K = "final"
story.append(PageBreak())
story += chapter_header("8", "Cheat Sheet and Exam Prep", "Compare all seven methods at a glance", K)
story.append(H2("Master comparison table", K))
story += grid_table([["Sort", "Best", "Average", "Worst", "Space", "Stable", "In-place", "Technique"],
                     ["Bubble", "O(n)", "O(n^2)", "O(n^2)", "O(1)", "Yes", "Yes", "Swap neighbours"],
                     ["Insertion", "O(n)", "O(n^2)", "O(n^2)", "O(1)", "Yes", "Yes", "Insert into sorted part"],
                     ["Shell", "O(n log n)", "≈ O(n^1.5)", "O(n^2)", "O(1)", "No", "Yes", "Gapped insertion"],
                     ["Merge", "O(n log n)", "O(n log n)", "O(n log n)", "O(n)", "Yes", "No", "Divide and merge"],
                     ["Quick", "O(n log n)", "O(n log n)", "O(n^2)", "O(log n)", "No", "Yes", "Pivot partition"],
                     ["Heap", "O(n log n)", "O(n log n)", "O(n log n)", "O(1)", "No", "Yes", "Heap + extract max"],
                     ["Radix", "O(d(n+k))", "O(d(n+k))", "O(d(n+k))", "O(n+k)", "Yes", "No", "Digit buckets"]],
                    [19 * mm, 21 * mm, 23 * mm, 23 * mm, 17 * mm, 15 * mm, 17 * mm, W - 135 * mm], K)
story.append(H2("Which one should I pick?", K))
story += grid_table([["Situation", "Best choice", "Why"],
                     ["Very small array, or nearly sorted data", "Insertion sort", "Tiny overhead, O(n) on sorted input"],
                     ["General-purpose, speed matters most", "Quick sort", "Fastest on average, in-place"],
                     ["Need guaranteed O(n log n) and stability", "Merge sort", "Same speed in all cases, stable"],
                     ["Need guaranteed O(n log n) with almost no extra memory", "Heap sort", "O(1) space, no bad inputs"],
                     ["Medium arrays, no recursion allowed", "Shell sort", "Simple loops, much better than insertion"],
                     ["Many integers with few digits", "Radix sort", "Beats n log n by avoiding comparisons"],
                     ["Teaching or very small lists", "Bubble sort", "Simplest to understand and write"]],
                    [62 * mm, 32 * mm, W - 94 * mm], K)
story.append(H2("Memory tricks", K))
story += bullets([
    "<b>Stable ones:</b> <b>B</b>ubble, <b>I</b>nsertion, <b>M</b>erge, <b>R</b>adix. <b>Unstable ones:</b> <b>S</b>hell, <b>Q</b>uick, <b>H</b>eap.",
    "<b>Always O(n log n):</b> merge and heap. <b>Has an O(n<super>2</super>) worst case but is fast on average:</b> quick (and shell with a poor gap sequence).",
    "<b>Needs extra array:</b> merge and radix. <b>Uses recursion stack:</b> merge and quick.",
    "<b>One line each:</b> Bubble – biggest bubbles up. Insertion – cards in hand. Shell – insertion with gaps. Merge – split then stitch. Quick – pivot then partition. Heap – build the tree, take the top. Radix – digit by digit.",
])
story.append(H2("Frequently asked exam questions (with short answers)", K))
qa = [["Question", "Short answer"],
      ["When is quick sort O(n^2)?", "When the pivot is always the smallest or largest element, e.g. sorted input with first/last element as pivot. Random or median-of-three pivots avoid it."],
      ["Why does merge sort need extra space?", "The merge step copies the two halves into temporary arrays so it can overwrite the original positions safely – O(n) extra."],
      ["Difference between insertion and Shell sort?", "Insertion compares and shifts adjacent items only; Shell first compares items gap positions apart, so elements travel long distances early and the final pass has little work."],
      ["Why is building a heap O(n) and not O(n log n)?", "Half of the nodes are leaves (no work) and most others sink only one or two levels, so the total work sums to a linear amount."],
      ["Can any sort beat O(n log n)?", "Not by comparisons alone. Radix (and counting) sort beat it by using digit values instead of comparing elements."],
      ["Which sorts are best for an already sorted array?", "Bubble (with flag) and insertion sort: O(n)."],
      ["Which sort after the k-th pass has the k largest items in place?", "Bubble sort."],
      ["Why must radix sort use a stable digit-sort?", "To keep the order created by earlier (less significant) digit passes."]]
story += grid_table(qa, [58 * mm, W - 58 * mm], K)
story.append(H2("Appendix – a small test program (C)", K))
story.append(P("Paste any one of the sorting functions from this guide above <b>main</b> and run it to test."))
story += code_block("""
#include <stdio.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11, 90, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before: "); printArray(arr, n);
    bubbleSort(arr, n);               // or insertionSort, shellSort, heapSort, radixSort
    // mergeSort(arr, 0, n - 1);      // merge sort takes (arr, left, right)
    // quickSort(arr, 0, n - 1);      // quick sort takes (arr, low, high)
    printf("After:  "); printArray(arr, n);
    return 0;
}
""", K, "C code – test driver")

doc.build(story)
print("done")