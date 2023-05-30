<div style="display: flex; align-items: center;">
  <img src="https://avatars.githubusercontent.com/u/131867390?s=200&v=4" alt="WattRex Logo" style="float: left; margin-right: 10px;">
    <h1>TowerPower, a regenerative battery cycler</h1>
</div>

## The project

### Introduction

The regenerative battery cycler is an innovative project aimed at providing a cost-effective, precise, and easy-to-build solution for testing batteries. It caters to a wide range of individuals and organizations, including researchers, R&D institutions, second life markets, and DIY energy enthusiasts who are interested in battery testing. The roots of this project trace back to 2018 when Pablo Pastor embarked on his PhD journey, focusing on machine learning for second life  batteries. During his research, he encountered a significant challenge: there was a scarcity of open-source aging databases. Determined to address this issue, Pastor and his team proposed creating  their own databases. However, due to budget constraints, they had to find an affordable solution. The initial concepts were developed within the Group of Power Electronics and Microelectronics (GEPM). 

Over time, these concepts evolved, prioritizing three key factors: cost, simplicity, and precision. In 2021, a group of power electronic engineers, software developers, and energy sector experts from the PTI-Transener platform, operated by the Spanish National Research Council (CSIC) joined forces to propel the project forward. The team is currently focused on adapting the regenerative battery cycler to accommodate various battery chemistries, ensuring its versatility and applicability across different industries. 

As part of the Pastor's thesis and the PTI-Transener project, we have made the decision to share the regenerative battery cycler as an open-source product. This approach aims to support other researchers and energy enthusiasts by providing them with a low-budget option for their studies. Additionally, we emphasize a structured development process, ensuring transparency and accountability. All steps, design decisions, and technical details, from initial system requirements to final schematics, bill of materials (BOM), and embedded code are openly shared, enabling others to replicate and build upon our work.

By providing a cost-effective, accessible, and open-source regenerative battery cycler: TowerPower. We aim to facilitate battery testing and contribute to the advancement of research and development in the field of energy storage.

### Working principle

TowerPower stands out as a bidirectional system, capable of both charging and discharging cells. This versatility allows for comprehensive testing and evaluation of batteries under various operating conditions. Moreover, unlike many low-end cyclers that dissipate energy as heat, TowerPower minimizes energy loss during the cycling process (taking into account system efficiency). By efficiently transferring energy from one battery to  another, this system proves to be significantly more economical to operate compared to chargers that rely on resistive discharging methods, which result in energy wastage. TowerPower optimizes energy utilization, ensuring a cost-effective and sustainable solution for battery testing and research.

TowerPower operates based on a DC-DC synchronous buck power converter, enabling energy transfer from a higher voltage input source to a lower voltage output where the device under test (DUT), such as a cell, is connected. The use of a buck converter allows control on the low voltage side while lacking control on the high voltage side, as seen in buck-boost converters. Moreover, the synchronous architecture of the converter enables bidirectional current flow, facilitating both charging and discharging processes.

To simplify the electronics and eliminate the need for energy transfer to the grid, the system uses an energy accumulator on the high voltage side. This can be achieved using a 12 V car battery or a stack of lithium cells with a voltage exceeding 5.5V. In our lab, a 6V high-capacity deep cycle gel Pb battery is used, allowing multiple cyclers to be connected in parallel.

The control of TowerPower is accomplished through a CAN bus interface, providing seamless communication between the cycler and the external controller. Additionally, a dedicated control software has been developed and released, enabling users to command test cycles and gather results effectively. [Repo here!](https://github.com/WattRex/Battery-Cyclers-Controler)

In this particular version of the cycler, a low-cost power device with integrated driver and transistors has been chosen. This decision not only reduces costs but also enhances the miniaturization of the product. Furthermore, the switching frequency of the converter has been increased, resulting in a smaller coil size, contributing to the overall cost and compactness of the system.

### Acknowledgements
This research has been developed within the CSIC Interdisciplinary Thematic Platform (PTI+) Transición Energética Sostenible+ (PTI-TRANSENER+) as part of the CSIC program for the Spanish Recovery, Transformation and Resilience Plan funded by the Recovery and Resilience Facility of the European Union, established by the Regulation (EU) 2020/2094. Funding from the Spanish Ministry of Science and Innovation under project MAFALDA (PID2021-126001OB-C32) is also acknowledged.


