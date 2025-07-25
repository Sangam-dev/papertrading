import pandas as pd

df= pd.read_csv('../data/stocks_sorted.csv')

df = df[['Name','Symbol']].dropna().sort_values('Name')
df.to_csv('../data/companies_sorted.csv', index=False)