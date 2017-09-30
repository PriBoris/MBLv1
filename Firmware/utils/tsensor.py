

TS_DATA = 682

TS_CAL1 = 669
TS_CAL2 = 912
T1 = 30
T2 = 130


T = (T2 - T1) / (TS_CAL2 - TS_CAL1) * (TS_DATA - TS_CAL1) + T1

print("T =", T)

