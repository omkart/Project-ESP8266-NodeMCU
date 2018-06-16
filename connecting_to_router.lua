do
wifi.setmode(wifi.STATION)
wifi.sta.config("hns","helloworld")
wifi.sta.connect()

tmr.alarm(1,1000,1,function()
if wifi.sta.getip()==nil then
print("Obtaining IP....")
else
tmrw.stop(1)
print("Got IP"..wifi.sta.getip())
end
end)
end