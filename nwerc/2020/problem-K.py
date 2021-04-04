text_in = input().strip()
text_out = input().strip()

sticky = set()
j = 0
for i in range(len(text_in)):
    while text_in[i] != text_out[j]:
        sticky.add(text_out[j])
        j += 1
    j += 1
if j < len(text_out):
    sticky.add(text_out[j])

print(''.join(map(str, sticky)))