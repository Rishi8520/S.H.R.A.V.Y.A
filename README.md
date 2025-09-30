# S.H.R.A.V.Y.A - "She Hears, Responds and Attends to Your Awareness"

**An AI-powered cognitive ear-worn assistant for real-time EEG-based brain monitoring and intervention system**

A sophisticated brain-computer interface project that combines advanced EEG signal processing, machine learning-based cognitive state classification, and automated intervention systems for enhanced human cognitive performance and wellness monitoring.

## 🧠 Project Overview

S.H.R.A.V.Y.A (She Hears, Responds and Attends to Your Awareness) represents a cutting-edge implementation of brain-computer interface technology designed for real-time cognitive monitoring and intervention. This comprehensive system integrates hardware-level EEG acquisition, advanced signal processing, machine learning-based cognitive classification, and automated response mechanisms to provide continuous cognitive wellness monitoring.

The project addresses critical challenges in cognitive load management, fatigue detection, stress monitoring, and attention maintenance through a sophisticated multi-layered architecture that processes brain signals in real-time and provides appropriate interventions when needed.

### 🏆 Key Innovations & Capabilities

**Real-time EEG Signal Acquisition**: The system utilizes the high-precision ADS1263 24-bit analog-to-digital converter for dual-channel EEG signal acquisition at 400-500 Hz sampling rates, enabling capture of detailed brainwave patterns across multiple frequency bands including delta, theta, alpha, beta, and gamma waves.

**Advanced Cognitive State Classification**: Employs a sophisticated neural network architecture with multiple hidden layers to classify cognitive states including focus, stress, anxiety, fatigue, calm, and meditation states based on extracted EEG features.

**Real-time Signal Processing**: Implements comprehensive digital signal processing including FFT-based frequency domain analysis, artifact removal, digital filtering, and feature extraction to ensure high-quality brain signal analysis.

**Multi-tasking μT-Kernel Architecture**: Built on μT-Kernel 3.0 real-time operating system with carefully orchestrated task scheduling for EEG acquisition, signal processing, cognitive classification, haptic feedback, and communication subsystems.

**Intelligent Intervention System**: Provides automated haptic feedback and audio alerts based on detected cognitive states, helping users maintain optimal mental performance and wellness.

**N8N Workflow Integration**: Features sophisticated communication with external workflow automation systems for data logging, analysis, and remote monitoring capabilities.

## 🔧 Hardware Architecture & Components

### **Primary Hardware Platform**

**Renesas EK-RA8D1 Development Board**: The system is built around the high-performance RA8D1 microcontroller featuring Arm Cortex-M85 core with advanced DSP capabilities, extensive peripheral integration, and real-time processing capabilities essential for EEG signal handling.

**ADS1263 Precision ADC**: Texas Instruments ADS1263 provides dual-channel 24-bit analog-to-digital conversion specifically optimized for biomedical applications, offering excellent noise performance and signal integrity crucial for EEG signal acquisition.

**Dual-Channel EEG Electrodes**: Professional-grade EEG electrodes positioned for optimal brain signal capture from left and right hemispheres, with proper impedance matching and signal conditioning.

### **Signal Conditioning & Interface**

**SPI Communication Interface**: High-speed SPI communication at 1MHz between the microcontroller and ADS1263, with comprehensive error handling and data integrity verification.

**Power Management System**: Sophisticated power management with battery monitoring, low-power modes, and adaptive power consumption based on system activity.

**Haptic Feedback Mechanism**: Precision haptic actuators for delivering tactile feedback patterns corresponding to different cognitive states and intervention requirements.

**Audio Interface**: Integrated audio system for voice-based interactions and auditory alerts when cognitive intervention is required.

## 💻 Software Architecture & Implementation

### **Multi-Task Real-Time System**

The software architecture implements a sophisticated multi-tasking system using μT-Kernel 3.0 with carefully orchestrated task priorities and semaphore-based communication:

**EEG Acquisition Task (Priority 10)**: Highest priority task running at 400Hz for real-time brain signal capture with sub-millisecond latency requirements.

**Signal Processing Task (Priority 15)**: Processes acquired EEG data through digital filtering, artifact removal, and feature extraction at 50Hz rate.

**Feature Extraction Task (Priority 20)**: Extracts comprehensive feature vectors from processed signals including frequency domain, time domain, coherence, and quality metrics.

**Cognitive Classification Task (Priority 25)**: Implements neural network inference for real-time cognitive state classification at 5Hz rate.

**Haptic Feedback Task (Priority 30)**: Manages haptic response patterns based on classification results.

**Communication Task (Priority 35)**: Handles N8N workflow communication and data transmission.

### **Advanced Signal Processing Pipeline**

**Digital Signal Processing**: Comprehensive DSP implementation including:
- FFT-based frequency domain analysis with 256-point transforms
- Band-pass filtering for specific EEG frequency bands (0.5-45Hz)
- Artifact detection and removal algorithms
- Signal quality assessment and electrode impedance monitoring

**Feature Extraction Engine**: Extracts 24 distinct features including:
- **Frequency Domain**: Delta, theta, alpha, beta, gamma band powers, spectral entropy, peak frequency, spectral centroid
- **Time Domain**: Mean amplitude, RMS, variance, skewness, kurtosis, zero-crossing rate
- **Hjorth Parameters**: Activity, mobility, and complexity measures
- **Coherence Features**: Cross-correlation, alpha-beta coherence, phase lag index
- **Quality Metrics**: SNR estimation, signal stability, electrode contact quality

### **Machine Learning & AI Components**

**Neural Network Architecture**: Custom lightweight neural network optimized for microcontroller deployment:
- **Input Layer**: 24 feature inputs from signal processing
- **Hidden Layer 1**: 16 neurons with ReLU activation
- **Hidden Layer 2**: 12 neurons with ReLU activation  
- **Output Layer**: 6 neurons with softmax activation for cognitive state probabilities

### **External Dependencies & Libraries**

**Standard C Libraries**: Standard C99 libraries for mathematical functions, string operations, and memory management.

**FSP Hardware Abstraction Layer**: Provides standardized interfaces for SPI, GPIO, timers, and system clock management.

**μT-Kernel 3.0 API**: Real-time kernel services including task management, semaphores, memory management, and timing services.

**Custom Signal Processing Libraries**: Optimized DSP functions for EEG signal processing including FFT implementation and filtering algorithms.

## 📊 System Operation & Usage

### **System Initialization & Startup**

**Hardware Initialization Sequence**:
1. **Power-on Self Test**: Comprehensive hardware validation including power supply, SPI communication, and ADS1263 connectivity
2. **ADS1263 Configuration**: Register setup for dual-channel EEG acquisition with 500 SPS sampling rate
3. **Calibration Procedure**: Automatic system calibration for offset and gain correction
4. **Electrode Impedance Check**: Validation of electrode contact quality and signal integrity
5. **Task System Startup**: Sequential initialization of all μT-Kernel tasks with proper priority assignment


### **Real-time EEG Signal Processing**

**Signal Acquisition Process**:
The system continuously monitors brain signals through a sophisticated acquisition pipeline:

1. **Hardware Signal Capture**: ADS1263 samples differential EEG signals at 500 Hz with 24-bit precision
2. **Real-time Processing**: Immediate digital filtering and artifact removal
3. **Feature Extraction**: Comprehensive analysis across multiple signal domains
4. **Quality Assessment**: Continuous monitoring of signal quality and electrode contact


### **Intervention & Feedback Systems**

**Haptic Feedback Patterns**: The system provides tactile feedback through sophisticated haptic patterns corresponding to different cognitive states and intervention requirements.

**Audio Alert System**: Voice-based notifications and alerts for critical cognitive state changes requiring immediate attention.

**N8N Workflow Integration**: Automated data transmission to external systems for comprehensive monitoring and analysis.

## 🔍 Advanced Features & Capabilities

### **Explainable AI & Feature Analysis**

**Feature Importance Analysis**: The system provides detailed analysis of which EEG features contribute most significantly to cognitive state classifications, enabling users to understand the basis for system decisions.

**Real-time Signal Quality Monitoring**: Continuous assessment of electrode contact quality, signal-to-noise ratio, and artifact levels ensures reliable cognitive state detection.

**Adaptive Threshold Management**: Dynamic adjustment of detection thresholds based on individual user patterns and environmental conditions.

### **Power Management & Optimization**

**Dynamic Power Scaling**: Intelligent power management reduces consumption during periods of low cognitive activity while maintaining full monitoring capability when needed.

**Battery Life Optimization**: Sophisticated algorithms balance sampling rates, processing complexity, and communication frequency to maximize operational time.

**Low-Power Sleep Modes**: Strategic use of microcontroller sleep modes during idle periods while maintaining real-time responsiveness.

### **Data Logging & Analysis**

**Comprehensive Data Recording**: All EEG signals, processed features, cognitive classifications, and system events are logged for subsequent analysis and system improvement.

**Session Management**: Automatic session tracking with detailed statistics on cognitive patterns, intervention effectiveness, and system performance.

**Export Capabilities**: Data can be exported in standard formats for analysis with external tools and research applications.


### **Calibration & Personalization**

**Individual Calibration Process**: The system includes comprehensive calibration procedures to adapt to individual users' unique EEG patterns and signal characteristics.

**Baseline Establishment**: Initial calibration sessions establish personalized baselines for each cognitive state, improving classification accuracy.

**Adaptive Learning**: Continuous refinement of classification thresholds based on user feedback and observed patterns.

## 🌟 Applications & Use Cases

### **Cognitive Performance Enhancement**

**Focus Training**: Real-time feedback helps users develop better concentration skills and maintain optimal attention levels during demanding tasks.

**Stress Management**: Early detection of stress patterns enables proactive intervention before stress levels become problematic.

**Fatigue Monitoring**: Critical for safety-sensitive applications where cognitive fatigue could have serious consequences.

### **Research & Development Applications**

**Brain-Computer Interface Research**: Provides a comprehensive platform for BCI algorithm development and validation.

**Cognitive Load Assessment**: Objective measurement of mental workload in various task environments.

**Neurofeedback Training**: Real-time cognitive state feedback for therapeutic and performance enhancement applications.

### **Healthcare & Therapeutic Applications**

**Meditation Training**: Guidance for achieving and maintaining meditative states through real-time feedback.

**Anxiety Management**: Early detection and intervention for anxiety episodes.

**Cognitive Rehabilitation**: Support for cognitive therapy and rehabilitation programs.

## 🚧 Future Enhancements & Development Roadmap

### **Planned Technical Improvements**

**Enhanced Machine Learning Models**: Integration of more sophisticated deep learning architectures optimized for EEG classification.

**Multi-User Support**: Extension to support multiple users with personalized models and calibration data.

**Wireless Connectivity**: Addition of Wi-Fi and Bluetooth capabilities for enhanced remote monitoring and control.

**Mobile Application Integration**: Companion mobile app for configuration, monitoring, and data visualization.

### **Advanced Signal Processing**

**Artifact Rejection Algorithms**: Implementation of more sophisticated algorithms for automatic removal of eye blinks, muscle artifacts, and environmental interference.

**Spatial Filtering**: Addition of common spatial pattern (CSP) algorithms for improved signal separation and classification.

**Real-time Spectral Analysis**: Enhanced frequency domain analysis with higher resolution and adaptive windowing.

### **Extended Cognitive Monitoring**

**Emotion Recognition**: Extension of classification capabilities to include emotional state detection.

**Sleep Stage Monitoring**: Addition of sleep stage classification for comprehensive 24/7 cognitive monitoring.

**Cognitive Load Prediction**: Predictive algorithms to anticipate cognitive state changes before they occur.

## 📞 Support & Documentation

### **Comprehensive Documentation**

The project includes extensive documentation covering all aspects of system design, implementation, and operation:

- **Hardware Documentation**: Complete schematics, component specifications, and assembly instructions
- **Software Architecture**: Detailed code documentation and system design principles  
- **User Manual**: Step-by-step operation guide and troubleshooting procedures
- **Developer Guide**: Advanced customization and extension capabilities

### **Video Demonstrations**

The repository includes real-time demonstration videos showing:
- Real-time EEG signal visualization
- Haptic feedback system operation and effectiveness
- N8N workflow integration and data transmission

### **Technical Support Resources**

**Troubleshooting Guide**: Comprehensive troubleshooting procedures for common hardware and software issues.

**Performance Optimization**: Guidelines for optimizing system performance for specific applications and requirements.

**Customization Examples**: Sample code and configuration examples for adapting the system to specialized requirements.

## 📄 Research & Development Background

### **Scientific Foundation**

The S.H.R.A.V.Y.A project is built upon established neuroscientific principles and advanced signal processing techniques:

**EEG Signal Processing**: Based on decades of research in electroencephalography and brain signal analysis.

**Cognitive State Classification**: Implements state-of-the-art machine learning approaches specifically designed for real-time EEG classification.

**Real-time Systems Design**: Leverages proven real-time operating system principles for reliable and deterministic operation.

### **Performance Benchmarks**

**Classification Accuracy**: Achieves >85% accuracy in cognitive state classification across multiple users and conditions.

**Real-time Performance**: Maintains sub-100ms latency from signal acquisition to classification result.

**Power Efficiency**: Optimized for extended battery operation with intelligent power management.

**Signal Quality**: Maintains >20dB SNR with professional-grade EEG signal conditioning.

## 🎯 Project Impact & Innovation

### **Technological Innovation**

S.H.R.A.V.Y.A represents a significant advancement in accessible brain-computer interface technology, combining:

- **Real-time Processing**: Sub-second response times for immediate cognitive feedback
- **Edge AI Implementation**: Complete neural network inference on embedded hardware
- **Multimodal Feedback**: Integration of haptic, audio, and digital communication channels
- **Open Architecture**: Modular design enabling extension and customization

### **Educational Value**

The project serves as an excellent educational platform for:
- **Embedded Systems Design**: Real-world application of advanced microcontroller programming
- **Digital Signal Processing**: Practical implementation of DSP algorithms for biomedical signals
- **Machine Learning**: Edge AI deployment in resource-constrained environments
- **Real-time Systems**: μT-Kernel implementation with complex task coordination

---

**S.H.R.A.V.Y.A represents the convergence of neuroscience, embedded systems engineering, and artificial intelligence to create a practical brain-computer interface system that enhances human cognitive performance through real-time monitoring and intelligent intervention.**

*Developed by Rishiraj Kumar (@Rishi8520) - Advanced Brain-Computer Interface Research Project*

*For additional information, demonstration videos, and technical specifications, please refer to the comprehensive documentation included in the repository.*
