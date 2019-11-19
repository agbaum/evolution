import numpy
import pandas as pd
import plotnine as p9

norgs = 0
org_log = [(0,0)]
with open("log.txt") as log_file:
    for line in log_file:
        fields = line.split(": ")

        if fields[1] == "Birth":
            norgs += 1
            org_log.append((int(fields[0]), norgs))

        if fields[1] == "Death":
            norgs -= 1
            org_log.append((int(fields[0]), norgs))

df = pd.DataFrame(org_log, columns = ['time', 'n_orgs'])


# print(df)

p = p9.ggplot(df, p9.aes('time', 'n_orgs')) + p9.geom_point()
p.save('n_orgs.png')

