import requests
import json

def getCapitalCity(country):
    URL=f"https://jsonmock.hackerrank.com/api/countries?name={country}"
    r=requests.get(url=URL)
    data=r.json()

    if len(data['data'])==0:
      return "-1"
    return data['data'][0]['capital']
    


print(getCapitalCity("Australia"))

# import requests
# import json

# URL="http://localhost:8000/organizations/1/user_analytics/"
# data={
#   "from_date": "2022-06-01",
#   "to_date": "2022-08-31",
#   "project_type": "ContextualTranslationEditing",
#   "download_csv": True
# }

# r=requests.post(url=URL,data=data)

# print(r.json())