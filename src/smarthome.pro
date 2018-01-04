#------------------------------------------------------------------------------
#
# Smarthome projects for home control
#
#------------------------------------------------------------------------------

TEMPLATE = subdirs

SUBDIRS = common \
          smarthomed \
          smarthome


CONFIG += ordered
CONFIG += qtc_runnable
