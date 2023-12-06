import serial
import csv

# Set the serial port and baud rate to match your Arduino
ser = serial.Serial('COM5', 115200)  

# Open a CSV file for writing
with open('dataset.csv', 'w', newline='') as csvfile:
    csv_writer = csv.writer(csvfile)

    # Write the header row if needed
    csv_writer.writerow(["gm_voc_v", "gm_no2_v", "gm_eth_v", "gm_co_v", "ens_tvoc", "ens_co2", "bme_temp", "bme_pressure", "bme_altitude", "bme_humidity", "target"])

    try:
        while True:
            # Read a line of data from the Arduino
            data = ser.readline().decode().strip()
            if data:
                gm_voc_v, gm_no2_v, gm_eth_v, gm_co_v, ens_tvoc, ens_co2, bme_temp, bme_pressure, bme_altitude, bme_humidity, target = data.split(",")
                csv_writer.writerow([gm_voc_v, gm_no2_v, gm_eth_v, gm_co_v, ens_tvoc, ens_co2, bme_temp, bme_pressure, bme_altitude, bme_humidity, target])
    except KeyboardInterrupt:
        # Close the serial port
        ser.close()

