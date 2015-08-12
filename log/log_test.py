#-------------------------------------------------------------------------------
# Name:        logger_test
# Purpose:
#
# Author:      wkx
#
# Created:     06-06-2012
# Copyright:   (c) wkx 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python
import logging
import logging.config

def main():
    #日志初始化
    LOG_FILENAME = r'd:\backup\program\wukexin\log\logging.conf'
    logging.config.fileConfig(LOG_FILENAME)
    logger = logging.getLogger("simple_log_example")

    #测试代码
    logger.debug("debug message")
    logger.info("info message")
    logger.warn("warn message")
    logger.error("error message")
    logger.critical("critical message")


if __name__ == '__main__':
    main()
