## Location based Advertisement delivery using VANET:

### Introduction

Mobile devices have ceased to be a novelty: smartphones and tablets now dwarf TV sets and desktop computers as the preferred way to consume multimedia content. Advertisers have followed suit, rapidly embracing a growing variety of mobile Devices. Among mobile devices, vehicles are playing an increasingly important role. The large amount of time drivers and passengers spend therein, coupled with the advanced capabilities of present- day and future on-board units, make them an ideal platform for mobile advertising especially location-specific advertising. For instance, business such as shops and restaurants can advertise their products to the vehicle drivers themselves, as an alternative to static billboards.
The benefit of targeted commercial is threefold: advertisers make more potential customers privy to their services and products; agents (e.g., Google) get better click- through prices and as an end result, better profits; clients are covered to a great deal with much less disruptive, and probably beneficial, content material fabric. Focused commercial is even more crucial in mobile eventualities, in which display screen sizes and interest span in addition restrict the range of advertisements that users can visualize in a given time.

### Overall Objective

* The recent advances in self-driving automobile and Internet-of-Things (IoT) have drawn attention back to Vehicular Ad-hoc Networks (VANETs) due to interests in safety and communication applications . 
Vehicles in VANETs are typically equipped with On Board Units (OBUs) that allows communication with other OBUs and Road Side Units (RSUs) . 
* Information such as road and traffic condition thus can be exchanged between vehicles and between vehicles and RSUs. 
* The development of information dissemination in VANETs has given rise to vehicular advertising that value-added services, such as the commercials of nearby gas stations and restaurants are delivered over OBUs to users. 
* The main objective is that it exploits the mobility of carriers (vehicles) that ads can spread rapidly within a short time as carriers are moving from one place to another and can always forward ads to new vehicles they come across.

### Overall Architecture
![Capture](https://github.com/Keerthu8999/LocationBasedAdVANET/assets/26524891/96f463f4-5dfb-46b1-8a19-1d6a1c628b11)




### Working Principle 

* In our proposed system, various merchants  send their advertisement of offers to a third party broker. The message contains details of the offers, the validity and the location of the store in which the offer is valid.Each merchant can also promote their advertisements to increase the reach. They quote and pay a particular amount to the broker to promote the content. The message will be <advertisement, validity, quote, location>.
* The broker holds all the advertisements from various merchants. After receiving the frames, the advertisements are ranked based on Priority ranking algorithm. The algorithm ranks based on the quote of the merchant and also the offers provided. A score is calculated based on the features, Quote and Offer. The broker also classifies the advertisement into various domains. The need for domains is explained later. Ranking and classification are disjoint events. After ranking and classification, the advertisement is forwarded to the appropriate Road Side Unit(RSU).
* The validity of the offer provided by the merchant determines the lifetime of the message in the broker’s storage. Once the offer expires, the message is deleted from the storage. The broker sends advertisements to RSUs based on the location of the store. The RSU present in the vicinity of the store receives the advertisement. 
* The message received by the RSU from the broker will contain the offer and the validity. The RSU stores this message till the offer is valid. RSU will send this message to the vehicle by a Infrastructure-to-Vehicle(I2V) communication. 
* Not all the vehicles receive every advertisement stored in the RSU. The advertisements are sent based on the user’s preference. To achieve this, the vehicle’s On Board Unit(OBU) will send a message to the RSU in it’s range that has the domains which the user is interested in. The RSU then selects the advertisements that fall under this category. Also, advertisements are filtered based on the vehicle type. The offers from some high-end stores need not be sent to all users. Hence, the audience number is being limited.
* The user preference sent to the RSU is computed by the OBU. The OBU has the history of the user. Using this history, the domains that the user will be interested are computed to recommend the offers. A user profile is determined based on the history which is then used to compute the user preference.
* The RSU attaches a frame ID to identify this message and then sends it to the OBU. The message received by the OBU from the RSU has a limited lifetime. The lifetime is determined by the  distance of the vehicle from the RSU. This distance is computed dynamically based on the location. The distance differs for rural, suburban, urban etc. areas.
* In addition to V2I and I2V communications, Vehicle-to-Vehicle(V2V) communication is enabled for wide reach of the advertisement which is ultimately the merchant’s goal. The vehicle communicates the received messages to other vehicles within a particular range. Again, not all vehicles will receive these messages. If their interests align, the messages are sent. This is achieved by checking their domain which is computed by the corresponding OBU.










