import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
df = pd.read_csv('serial_results.csv', header=None, names=['Threads', 'Avg Execution Time', 'Standard Deviation'])

# Plot the average execution time vs. number of threads
plt.figure(figsize=(10, 6))
plt.errorbar(df['Threads'], df['Avg Execution Time'], yerr=df['Standard Deviation'], fmt='-o', capsize=5, label='Avg Execution Time')

# Add labels and title
plt.xlabel('Number of Threads')
plt.ylabel('Average Execution Time (seconds)')
plt.title('Average Execution Time vs Number of Threads')
plt.grid(True)
plt.legend()

# Show the plot
plt.show()
