import csv

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1

        while j >= 0 and arr[j][0].lower() > key[0].lower():
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def main():
    file_path = '/home/sangam/programming/dsa/DSA-Trader/data/stocks1.csv'
    data = []


    with open(file_path, 'r', newline='', encoding='utf-8') as file:
        reader = csv.reader(file)
        header = next(reader) 
        for row in reader:

            if len(row) >= 2:
                data.append((row[0].strip(), row[1].strip()))


    sorted_data = insertion_sort(data)


    with open(file_path, 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(header)
        writer.writerows(sorted_data)

main()
