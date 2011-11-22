Realtime monitoring system of a packaging line.

## Systems
- Monitoring computer (Windows)
- Packaging system (VxWorks)

## Network
- Sockets (TCP/IP)

## Synopsis
- Parts come through Trap
- Parts get measured by Sensor (OK/defective)
- Parts are conditioned into Box
- Printer prints status report
- Boses are put in Queue (max 10)
- Boxes are combined into Palette
- Palettes are stored in Warehouse

## Errors
- Emergency Stop
- No box found
- Printer failure
- Too many defective parts in box
- Missing parts
- Queue full
- No palette found

## Error handling
- Close trap
- Prompt supervisor (stop/restart)
- Log event
