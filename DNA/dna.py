from sys import argv, exit
import csv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    STRs = list()
    profiles = list()
    with open(argv[1], mode="r") as database:
        obj = csv.DictReader(database)
        STRs = obj.fieldnames[1:]
        for row in obj:
            profiles.append(row)

    seq_count = dict.fromkeys(STRs, 0)

    with open(argv[2], mode="r") as sequence_file:
        sequence = sequence_file.readline()
        for STR in STRs:
            seq_count[STR] = find_repeats(sequence, STR)

    for profile in profiles:
        count = 0
        for STR in STRs:
            if int(profile[STR]) != seq_count[STR]:
                continue
            count += 1
        if count == len(STRs):
            print(profile['name'])
            exit(0)
    print("No match")
    exit(1)


def find_repeats(sequence, STR):
    L = len(STR)
    max = 0
    for i in range(len(sequence)):
        repeats = 0
        if sequence[i: i + L] == STR:
            repeats += 1
            while sequence[i: i + L] == sequence[i + L: i + (2 * L)]:
                repeats += 1
                i += L
        if repeats > max:
            max = repeats
    return max

if __name__ == "__main__":
    main()
